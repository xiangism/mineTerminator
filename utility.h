#pragma once
#include "Block.h"
#include <shangjing/TwoDimesionArray.hpp>

using namespace shangjing;

inline bool isInArrary(TwoDimesionArray<Block> &blocks,int x,int y)
{
    if(x<0||x>=blocks.GetWidth() || y<0||y>=blocks.GetHeight())
    {
        return false;
    }
    return true;
}


inline int calMine(TwoDimesionArray<Block> &blocks, int x,int y)  //��֪�жϳ�������
{
    int count=0;
    for (int i=0;i<8;++i)
    {
        if (isInArrary(blocks,x+g_around[i][0],y+g_around[i][1]))
        {
            if(blocks.GetValue(x+g_around[i][0],y+g_around[i][1]).m_mineState==MineState::IsMine)
            {
                ++count;
            }
        }
    }
    return count;
}

//������δ��ʾ�Ŀ飬����֪���ǲ�����
inline int calHide(TwoDimesionArray<Block> &blocks,int x,int y)
{
    int count=0;
    for (int i=0;i<8;++i)
    {
        if (isInArrary(blocks,x+g_around[i][0],y+g_around[i][1]))
        {
            if(blocks.GetValue(x+g_around[i][0],y+g_around[i][1]).m_isHide)
            {
                ++count;
            }
        }
    }
    return count;
}