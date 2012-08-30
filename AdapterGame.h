#pragma once
#include "Block.h"
#include <shangjing/TwoDimesionArray.hpp>
#include <vector>
#include <utility>
using namespace std;
using namespace shangjing;

//��Ϸ������״̬�����С�ʧ�ܽ������ɹ�����
enum GameState
{
    GameRun=1,
    GameOver,
    GameWin,
    GameClose
};

//��Ϸ�����ֲ�ͬ�Ѷȼ���
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
    virtual bool clickPieces(TwoDimesionArray<Block> blocks)=0;  //�����Ƿ�������֣����޷��жϵľ��档���������򷵻�false
    virtual void clickPiece(pair<int,int> &minOne)=0;
    
private:
    void moveShowWindow();

protected:
    HWND m_gameHandle;
    RECT m_gameRect;
    TwoDimesionArray<RGBQUAD> m_gameColors;
    GameType m_gameType;
    int mineTotal;    //��Ϸ�����׵�����

};
//����û�ʶ�����е�����������������ӵĿ�ʹ��ʺŵĿ�