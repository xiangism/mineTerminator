#pragma once
#include "Block.h"
#include <shangjing/TwoDimesionArray.hpp>
#include <vector>
#include <utility>
using namespace std;
using namespace shangjing;

//游戏的三种状态，运行、失败结束、成功结束
enum GameState
{
    GameRun=1,
    GameOver,
    GameWin,
    GameClose
};

//游戏的三种不同难度级别
enum GameType
{
    GameLow=1,
    GameMid,
    GameHigh,
    GameException
};

class AdapterGame
{
public:
    AdapterGame(void);
    ~AdapterGame(void);    
    
    void findGameWindow();
    int getMineTotal()const {return mineTotal;}
    virtual GameType getGameType()=0;
    virtual GameState getGameState()=0;
    virtual TwoDimesionArray<Block> getGameData()=0;
    virtual bool clickPieces(TwoDimesionArray<Block> blocks)=0;  //返回是否进入死局，即无法判断的局面。进入死局则返回false
    virtual void clickPiece(pair<int,int> &minOne)=0;
    
private:
    void moveShowWindow();

protected:
    HWND m_gameHandle;
    RECT m_gameRect;
    TwoDimesionArray<RGBQUAD> m_gameColors;
    GameType m_gameType;
    int mineTotal;    //游戏池中雷的总数

};
//必须得会识别所有的情况，包括插上旗子的块和打问号的块