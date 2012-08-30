#pragma once
#include <vector>
#include <utility>
using namespace std;

class ProbableMine
{
public:
    int mineCount;
    vector<pair<int,int>> points;

    ProbableMine(int count)
        :mineCount(count)
    {
    }
    void addPoint(int x,int y)
    {
        points.push_back(make_pair(x,y));
    }
    void addPoint(pair<int,int> p)
    {
        points.push_back(p);
    }
    bool isEque(const ProbableMine &pm)
    {
        if(mineCount !=pm.mineCount)
            return false;
        if(points.size()!=pm.points.size())
            return false;
        if(getPointValue()!=pm.getPointValue())
            return false;
        return true;
    }

private:
    //�����൱�ڷ���һ��points�Ĺ�ϣֵ
    //��֪�������᲻�����ظ�ֵ
    long getPointValue() const
    {
        long value=0;
        for (int i=0;i<points.size();++i)
        {
            value += points[i].first*1000;
            value+=points[i].second;
        }
        return value;
    }
};
