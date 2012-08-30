#pragma once
#include <shangjing/TwoDimesionArray.hpp>
#include "Block.h"
#include "ProbableMine.h"

using namespace shangjing;

class EstimateAnalyse
{
public:
    EstimateAnalyse(void);
    ~EstimateAnalyse(void);
    TwoDimesionArray<double> getEstimate(TwoDimesionArray<Block> blocks,vector<ProbableMine> probables,int mineTotal);

private:
    
};
