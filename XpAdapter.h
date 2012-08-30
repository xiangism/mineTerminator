#pragma once
#include "adaptergame.h"
#include <utility>
using namespace std;

class XpAdapter :  public AdapterGame
{
public:
    XpAdapter(void);
    ~XpAdapter(void);
    GameType getGameType();
    GameState getGameState();
    TwoDimesionArray<Block> getGameData();
    bool clickPieces(TwoDimesionArray<Block> blocks);
    void clickPiece(pair<int,int> &minOne);

private:
    void getOne(TwoDimesionArray<Block> blocks, int x,int y);

private:
     pair<int,int> firstClick;
};
