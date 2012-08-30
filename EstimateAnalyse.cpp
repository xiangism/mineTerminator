#include "StdAfx.h"
#include "EstimateAnalyse.h"


EstimateAnalyse::EstimateAnalyse(void)
{
}

EstimateAnalyse::~EstimateAnalyse(void)
{
}

TwoDimesionArray<double> EstimateAnalyse::getEstimate(TwoDimesionArray<Block> blocks,vector<ProbableMine> probables,int mineTotal)
{
    TwoDimesionArray<double> estimates(blocks.GetWidth(),blocks.GetHeight());
    estimates.SetAllValue(1.1);
    int unKownCount=0;
    int isMineCount=0;
    for (int i=0;i<blocks.GetWidth();++i)
    {
        for (int j=0;j<blocks.GetHeight();++j)
        {
            const Block &b=blocks.GetValue(i,j);
            if(b.m_isHide  )
            {
                if( b.m_mineState==MineState::UnKown)
                {
                    ++unKownCount;
                }
                else if(b.m_mineState==MineState::IsMine)
                {
                    ++isMineCount;
                }
            }
        }
    }

    double  leaveF=(mineTotal-isMineCount)*1.0/unKownCount  ; //还剩下的雷数/还剩下的未知块
    for (int i=0;i<blocks.GetWidth();++i)
    {
        for (int j=0;j<blocks.GetHeight();++j)
        {
            const Block &b=blocks.GetValue(i,j);
            if(b.m_isHide && b.m_mineState==MineState::UnKown)
            {
                estimates.SetValue(i,j,leaveF);
            }

        }
    }
    for (int i=0;i<probables.size();++i)
    {
        const ProbableMine &p=probables[i];
        double f=p.mineCount *1.0/p.points.size();
        //estimates.GetValue()
        for (int j=0;j<p.points.size();++j)
        {
            estimates.SetValue(p.points[j].first,p.points[j].second,f);
        }
    }

    return estimates;
}