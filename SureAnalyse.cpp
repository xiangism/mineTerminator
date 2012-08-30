#include "StdAfx.h"
#include "SureAnalyse.h"
#include "AnalyseData.h"
#include "utility.h"
#include <algorithm>

SureAnalyse::SureAnalyse()
{
}

SureAnalyse::~SureAnalyse(void)
{
}
 
void SureAnalyse::addProbables(TwoDimesionArray<Block> blocks)
{
    for (int i=0;i<blocks.GetWidth();++i)
    {
        for (int j=0;j<blocks.GetHeight();++j)
        {
            Block &b=blocks.GetValue(i,j);
            if(!b.m_isHide && b.m_aroundMineCount!=0 && b.m_aroundMineCount> calMine(blocks,i,j))
            {
                addProbable(i,j);
            }
        }
    }
}


void SureAnalyse::addProbable(int x, int y)
{
    //��Χ��δȷ���Ŀ�ĸ���
    int unKownCount=0;
    for (int i=0;i<8;++i)
    {
        int a=x+g_around[i][0];
        int b=y+g_around[i][1];
        if (isInArrary(m_blocks,a,b))
        {
            Block &block=m_blocks.GetValue(a,b);
            if (block.m_isHide && block.m_mineState==MineState::UnKown)
            {
                ++unKownCount;
            }
        }
    }

    int t=m_blocks.GetValue(x,y).m_aroundMineCount - calMine(m_blocks,x,y);  //��δ���ֵ�����
    //��Χδȷ���ĸ������ڻ�δ���ֵ��׵ĸ���
    if(unKownCount>t)
    {
        ProbableMine pm(t);
        for (int i=0;i<8;++i)
        {
            int a=x+g_around[i][0];
            int b=y+g_around[i][1];
            if (isInArrary(m_blocks,a,b))
            {
                Block &block=m_blocks.GetValue(a,b);
                if (block.m_isHide && block.m_mineState==MineState::UnKown)
                {
                    //++unKownCount;
                    pm.addPoint(a,b);
                }
            }
        }
        //surer->addProbable(pm);
        if(!isExitProbable( pm))
        {
            probables.push_back(pm);
        }
    }
}


bool SureAnalyse::isExitProbable(const ProbableMine &pm)
{
    for (int i=0;i<probables.size();++i)
    {
        if(probables[i].isEque(pm))
            return true;
    }
    return false;
}


void SureAnalyse::getSure(TwoDimesionArray<Block> blocks)
{
    m_blocks=blocks;
    probables.clear();
    m_Mines.clear();
    m_notMines.clear();
    addProbables(blocks);

     while(1)
     {
         bool m_isChangedProbable=false;
          for (int i=0;i<probables.size();++i)
          {
              for (int j=0;j<probables.size();++j )
              {
                  if(i==j)
                      continue;
                  if(probables[i].mineCount>=probables[j].mineCount &&
                      probables[i].points.size() > probables[j].points.size() )
                  {
                      vector<int> sites;
                      for (int b=0;b<probables[j].points.size();++b)
                      {
                          for (int a=0;a<probables[i].points.size();++a)
                          {
                              if(probables[j].points[b]==probables[i].points[a])
                              {
                                  sites.push_back(a);  //������ӵ���a����probales[i] �е�index
                                  break;
                              }
                          }
                      }//end two for
                      //���probables[j] ��i��һ���Ӽ����������������ProbableMine�ó�һ���µ�
                       if(sites.size()== probables[j].points.size())
                       {
                            ProbableMine newPm(probables[i].mineCount - probables[j].mineCount);
                            for (int k=0;k<probables[i].points.size();++k)
                            {
                                if(find(sites.begin(),sites.end(),k)==sites.end())
                                {
                                    newPm.addPoint(probables[i].points[k]);
                                }
                            }
                            //��Щ�㶼������
                            if(newPm.mineCount==0)
                            {
                                for (int k=0;k<newPm.points.size();++k)
                                {
                                    //�ж��Ƿ��Ѿ����
                                    if(find(m_notMines.begin(),m_notMines.end(),newPm.points[k]) ==m_notMines.end() )
                                    {
                                        m_notMines.push_back(newPm.points[k]);
                                    }

                                }
                               
                            }
                            //��Щ�㶼����
                            else if(newPm.mineCount==newPm.points.size())
                            {
                                for (int k=0;k<newPm.points.size();++k)
                                {
                                    if(find(m_Mines.begin(),m_Mines.end(),newPm.points[k])==m_Mines.end())
                                    {
                                        m_Mines.push_back(newPm.points[k]);
                                    }                                  
                                }
                            }
                            else
                            {
                                if(!  isExitProbable(newPm))
                                {
                                    probables.push_back(newPm);
                                    m_isChangedProbable=true;
                                }
                            }
                       }
                  }
              }
          }//end two for
        if(!m_isChangedProbable)
            break;
     }//end while
}

const vector<pair<int,int>>& SureAnalyse::getMines()const
{
    return m_Mines;
}

const vector<pair<int,int>>& SureAnalyse::getNotMines()const
{
    return m_notMines;
}