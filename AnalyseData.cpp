#include "StdAfx.h"
#include "AnalyseData.h"
#include "SureAnalyse.h"
#include "EstimateAnalyse.h"
#include "utility.h"

AnalyseData::AnalyseData( )
{
    surer=shared_ptr<SureAnalyse>(new SureAnalyse());
}

AnalyseData::~AnalyseData(void)
{
}

void AnalyseData::run(TwoDimesionArray<Block> blocks)
{
    m_blocks=blocks;
    scanOne();
}

pair<int,int> AnalyseData::getEstimate(int mineTotal)
{
    EstimateAnalyse estimater;
    TwoDimesionArray<double> es= estimater.getEstimate(m_blocks,surer->getProbables(),mineTotal);
    pair<int,int> minPair=make_pair(-1,-1);
    double value=2;
    for (int i=0;i<es.GetWidth();++i)
    {
        for (int j=0;j<es.GetHeight();++j)
        {
            if(es.GetValue(i,j)<value)
            {
                minPair.first=i;
                minPair.second=j;
                value=es.GetValue(i,j);
            }
        }
    }
    return minPair;
}

void AnalyseData::scanOne()
{
    while(1)
    {
        m_isChanged=false;
        for (int i=0;i<m_blocks.GetWidth();++i)
        {
            for (int j=0;j<m_blocks.GetHeight();++j)
            {
                Block &b=m_blocks.GetValue(i,j);
                //�Ѿ���ʾ�ˣ��������ֲ�Ϊ0����������Ϊ0�Ŀ�û�����۵�����-��Ϊ��Χ���Զ��㿪
                if( !b.m_isHide &&b.m_aroundMineCount!=0)
                {
                    int hideCount=calHide(m_blocks,i,j);
                    //�����Χδ��ʾ�ĸ�����������������Щ�Ͷ�������
                    if(hideCount==b.m_aroundMineCount)
                    {
                        addAroundMines(i,j);
                    }
                    int mineCount=calMine(m_blocks,i,j);
                    //�����Χ���׵ĸ�������������������δ�жϵľͶ�������
                    if(mineCount == b.m_aroundMineCount)
                    {
                        addAroundNotMines(i,j);
                    }
                }
            }
        }
        if(!m_isChanged)
            break;
    }
        
    surer->getSure( m_blocks);
    vector<pair<int,int>> mine=surer->getMines();
    vector<pair<int,int>> notMine=surer->getNotMines();
    for (int i=0;i<mine.size();++i)
    {
        m_blocks.GetValue(mine[i].first,mine[i].second).m_mineState=MineState::IsMine;
    }
    for (int i=0;i<notMine.size();++i)
    {
        m_blocks.GetValue(notMine[i].first,notMine[i].second).m_mineState=MineState::NotMine;
    }
    if( (!mine.empty())||(!notMine.empty()))  //�жϳ��׻���û���׺���ٽ����ж�
    {
        scanOne();
    } 
}


//ֻҪ��û����ʾ�ĵط�������
void AnalyseData::addAroundMines(int x,int y)
{
    for (int i=0;i<8;++i)
    {
        if (isInArrary(m_blocks,x+g_around[i][0],y+g_around[i][1]))
        {
            Block &b=m_blocks.GetValue(x+g_around[i][0],y+g_around[i][1]);
            if(b.m_isHide && b.m_mineState==MineState::UnKown )
            {
                b.m_mineState=MineState::IsMine;
                m_isChanged=true;
            }
        }
    }
}

//δ��ʾ�����һ�û���ж��Ƿ����׵ĵط����������Ϊ������
void AnalyseData::addAroundNotMines(int x,int y)
{
    for (int i=0;i<8;++i)
    {
        if (isInArrary(m_blocks,x+g_around[i][0],y+g_around[i][1]))
        {
            Block &b=m_blocks.GetValue(x+g_around[i][0],y+g_around[i][1]);
            if(b.m_isHide && 
                b.m_mineState==MineState::UnKown )
            {
                b.m_mineState=MineState::NotMine;
                m_isChanged=true;
            }
        }
    }
}
