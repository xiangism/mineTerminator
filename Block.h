#pragma once

//�������׵�������������������
//һ���������δ֪��
//ͨ���������Եó����׻�����
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
    int m_aroundMineCount;    //�������ֻ����m_isHideΪfalseʱ��������

    MineState m_mineState;    //�������ֻ����m_isHideΪtrueʱ��������
};
