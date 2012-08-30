#pragma once
#include "Block.h"
#include "AdapterGame.h"
#include <shangjing/TwoDimesionArray.hpp>
#include <boost/shared_ptr.hpp>
using namespace shangjing;
using namespace boost;

class AnalyseData;
class AdapterGame;

class GamePanel
{    
public:
    GamePanel(void);
    ~GamePanel(void);
    GameState allRun();   //全自动 ，直到游戏结束或游戏胜利，用户来选择重新开始
    void semiRun();         //半自动，只点出确定不是雷的块
    
private:
    shared_ptr<AnalyseData> analyser;
    shared_ptr<AdapterGame> adapter;

};
