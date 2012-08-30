#include "StdAfx.h"
#include "GamePanel.h"
#include "AnalyseData.h"
#include "AdapterGame.h"
#include "XpAdapter.h"
#include <shangjing/windows/system.hpp>

GamePanel::GamePanel(void)
{
    if(shangjing::windows::isXpOS())
    {
        adapter=shared_ptr<AdapterGame>(new XpAdapter());      
    }
    analyser=shared_ptr<AnalyseData>(new AnalyseData());
}

GamePanel::~GamePanel()
{
}

GameState GamePanel::allRun()
{
    //这个函数一直运行，直到gameOver 或gameWin
    adapter->findGameWindow();
    GameState stata=adapter->getGameState();
    if(stata==GameState::GameRun)
    {
        analyser->run(adapter->getGameData());
        if(!adapter->clickPieces(analyser->getBlocks()))
        {
            pair<int,int> minOne= analyser->getEstimate(adapter->getMineTotal());
            adapter->clickPiece(minOne);
        }
    }
    return stata;
}

void GamePanel::semiRun()
{
    //这个函数一直运行，直到clickPieces返回false，即没有可以点击的块
    adapter->findGameWindow();
    GameState stata=adapter->getGameState();
    if(stata==GameState::GameRun)
    {
        analyser->run(adapter->getGameData());
        if(!adapter->clickPieces(analyser->getBlocks()))
        {
            return;
        }
    }
}
