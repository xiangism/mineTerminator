#pragma once
#include <vector>
#include "ProbableMine.h"
#include "Block.h"
#include <shangjing/TwoDimesionArray.hpp>

using namespace shangjing;
using namespace std;

//通过这个类的分析即可以得出哪些块是雷，也可以得出哪些块不是雷
//1,2,3:2
//1,2:1     =>3:0 (可得3号块没有雷)

//1,2,3,4,5:4
//1,2:1             =>3,4,5:3 (3,4,5号块都是雷)

class SureAnalyse
{
public:
    SureAnalyse();
    ~SureAnalyse(void);     
    
    void getSure(TwoDimesionArray<Block> blocks);    //从可能性中获取确定的块状态
    const vector<pair<int,int>>& getMines()const;
    const vector<pair<int,int>>& getNotMines()const;
    vector<ProbableMine> &getProbables(){return probables;}

private:
    void addProbable(int x, int y);
    void addProbables(TwoDimesionArray<Block> blocks);
    bool isExitProbable(const ProbableMine &pm);

private:
    TwoDimesionArray<Block> m_blocks;
    vector<ProbableMine> probables; //所有的可能情况
    vector<pair<int,int>> m_Mines; //保存结果
    vector<pair<int,int>> m_notMines;//保存结果
    
};
