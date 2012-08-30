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
    void scanOne();  //进行确定雷的扫描
    void estimateOne();
    
    //int calMine(int x,int y);   //求一个广场周围已确定的雷的个数   
    //int calHide(int x,int y);  //求一个数字周围未显示的方块个数
    //bool isInArrary(int x,int y); 
    void addAroundMines(int x,int y);   //周围未显示的都是雷
    void addAroundNotMines(int x,int y);    //周围未显示，并且未知的都不是雷
    void addProbable(int i, int j );    //以一个块添加可能有雷的情况
    
};
