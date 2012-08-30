#pragma once

//方块上雷的情况，这里有三种情况
//一般情况下是未知的
//通过分析可以得出是雷或不是雷
enum MineState
{
    UnKown=1,
    IsMine,
    NotMine
};

class Block
{
public:
    Block():m_isHide(true),m_aroundMineCount(-1),m_mineState(UnKown)
    {

    }
public:
    bool m_isHide;
    int m_aroundMineCount;    //这个属性只有在m_isHide为false时才有意义

    MineState m_mineState;    //这个属性只有在m_isHide为true时才有意义
};
