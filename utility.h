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


inline int calMine(TwoDimesionArray<Block> &blocks, int x,int y)  //已知判断出的雷数
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

//仅仅是未显示的块，还不知道是不是雷
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