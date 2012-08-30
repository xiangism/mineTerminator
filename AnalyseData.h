#pragma once
#include "Block.h"
#include "ProbableMine.h"
#include <shangjing/TwoDimesionArray.hpp>
#include <boost/shared_ptr.hpp>

using namespace shangjing;

const static int g_around[8][2]={
    -1,-1,
    -1,0,
    -1,1,
    0,-1,
    0,1,
    1,-1,
    1,0,
    1,1
};
class SureAnalyse ;
class AnalyseData
{
private:
    //vector<pair<int,int>> mines;
    TwoDimesionArray<Block> m_blocks;
    bool m_isChanged;
    shared_ptr<SureAnalyse> surer;

public:
    AnalyseData();
    ~AnalyseData(void);
    const TwoDimesionArray<Block>& getBlocks() const {return m_blocks;}
    void run(TwoDimesionArray<Block> blocks);
    pair<int,int> getEstimate(int mineTotal);

private:
    void scanOne();  //����ȷ���׵�ɨ��
    void estimateOne();
    
    //int calMine(int x,int y);   //��һ���㳡��Χ��ȷ�����׵ĸ���   
    //int calHide(int x,int y);  //��һ��������Χδ��ʾ�ķ������
    //bool isInArrary(int x,int y); 
    void addAroundMines(int x,int y);   //��Χδ��ʾ�Ķ�����
    void addAroundNotMines(int x,int y);    //��Χδ��ʾ������δ֪�Ķ�������
    void addProbable(int i, int j );    //��һ������ӿ������׵����
    
};
