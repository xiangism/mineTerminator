#pragma once
#include <vector>
#include "ProbableMine.h"
#include "Block.h"
#include <shangjing/TwoDimesionArray.hpp>

using namespace shangjing;
using namespace std;

//ͨ�������ķ��������Եó���Щ�����ף�Ҳ���Եó���Щ�鲻����
//1,2,3:2
//1,2:1     =>3:0 (�ɵ�3�ſ�û����)

//1,2,3,4,5:4
//1,2:1             =>3,4,5:3 (3,4,5�ſ鶼����)

class SureAnalyse
{
public:
    SureAnalyse();
    ~SureAnalyse(void);     
    
    void getSure(TwoDimesionArray<Block> blocks);    //�ӿ������л�ȡȷ���Ŀ�״̬
    const vector<pair<int,int>>& getMines()const;
    const vector<pair<int,int>>& getNotMines()const;
    vector<ProbableMine> &getProbables(){return probables;}

private:
    void addProbable(int x, int y);
    void addProbables(TwoDimesionArray<Block> blocks);
    bool isExitProbable(const ProbableMine &pm);

private:
    TwoDimesionArray<Block> m_blocks;
    vector<ProbableMine> probables; //���еĿ������
    vector<pair<int,int>> m_Mines; //������
    vector<pair<int,int>> m_notMines;//������
    
};
