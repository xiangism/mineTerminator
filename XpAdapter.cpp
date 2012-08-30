#include "StdAfx.h"
#include "XpAdapter.h"
#include <shangjing/windows/image.hpp>
#include <shangjing/image/baseAlgorithm.hpp>

using shangjing::image::isColorEqual;
XpAdapter::XpAdapter(void)
{
firstClick=make_pair(17,60);
}

XpAdapter::~XpAdapter(void)
{
}


GameType XpAdapter::getGameType()
{
    int width=m_gameRect.right-m_gameRect.left;
    int height=m_gameRect.bottom-m_gameRect.top;
    if(width==170 && height==251)
    {
        return GameType::GameLow;
    }
    if(width==282&&height==363)
    {
        return GameType::GameMid;
    }
    if(width==506 &&height==363)
    {
        return GameType::GameHigh;
    }
    return GameType::GameException;
}

GameState XpAdapter::getGameState()
{
    if(!m_gameHandle)
    {
        return GameState::GameClose;
    }
    return GameState::GameRun;
}

TwoDimesionArray<Block> XpAdapter::getGameData()
{
    TwoDimesionArray<Block> blocks;
    if(m_gameType==GameType::GameLow)
    {
        blocks=TwoDimesionArray<Block>(9,9);
        mineTotal=10;
    }
    else if(m_gameType==GameType::GameMid)
    {
        blocks=TwoDimesionArray<Block>(16,16);
        mineTotal=40;
    }
    else if(m_gameType==GameType::GameHigh)
    {
        blocks=TwoDimesionArray<Block>(30,16);
        mineTotal=99;
    }
    m_gameColors=shangjing::windows::CaptureScreen(&m_gameRect);
    for (int i=0;i<blocks.GetWidth();++i)
    {
        for (int j=0;j<blocks.GetHeight();++j)
        {
            getOne(blocks,i,j);
        }
    }    
    return blocks;
}

void XpAdapter::getOne(TwoDimesionArray<Block> blocks, int x,int y)
{
    pair<int,int> firstSite=make_pair(17,104);
    pair<int,int> firstSiteHide=make_pair(30,111);

    const RGBQUAD &c=m_gameColors.GetValue(firstSiteHide.first +x*16,firstSiteHide.second+y*16 );

    RGBQUAD cc[]=
    {
        {255,0,0},
        {0,128,0},
        {0,0,255},
        {128,0,0},
        {0,0,128},
        {128,128,0},
        {0,0,0},
        {128,128,128},
    };

    if(c.rgbRed==128&&c.rgbGreen==128&&c.rgbBlue==128)
    {
        //blocks.GetValue(x,y).m_isHide=true;
    }
    else
    {
        blocks.GetValue(x,y).m_isHide=false;
        for (int k=0;k<12;++k)
        {
            const RGBQUAD &t=m_gameColors.GetValue(firstSite.first+x*16+k,firstSite.second+y*16);
            /*     if(isColorEqual(cc[0],t))
            {
            blocks.GetValue(x,y).m_aroundMineCount=1;
            break;
            }
            else if(isColorEqual(cc[1],t))
            {
            blocks.GetValue(x,y).m_aroundMineCount=2;
            break;
            }*/
            for (int m=0;m<8;++m)
            {
                if(isColorEqual(cc[m],t))
                {
                    blocks.GetValue(x,y).m_aroundMineCount=m+1;
                    //goto OUTFOR;
                    return;
                }
            }
        }

        //OUTFOR
    }
}

bool XpAdapter::clickPieces(TwoDimesionArray<Block> blocks)
{
    //POINT p;
    //GetCursorPos(&p);
 /*  int clickOneX=m_gameRect.left +100;
    int clickOneY=m_gameRect.top+60;
    SetCursorPos(clickOneX,clickOneY);
    mouse_event(MOUSEEVENTF_LEFTDOWN,clickOneX,clickOneY,0,0);
    mouse_event(MOUSEEVENTF_LEFTUP,clickOneX,clickOneY,0,0); 
 */
    bool haveNotMine=false;
    
    for (int i=0;i<blocks.GetWidth();++i)
    {
        for (int j=0;j<blocks.GetHeight();++j)
        {
            if(blocks.GetValue(i,j).m_mineState==MineState::NotMine)
            {
                int x=/*m_gameRect.left +*/ firstClick.first + i*16;
                int y=/*m_gameRect.top + */firstClick.second +j*16;
                //SetCursorPos(x,y);
                //mouse_event(MOUSEEVENTF_LEFTDOWN,x,y,0,0);
                //mouse_event(MOUSEEVENTF_LEFTUP,x,y,0,0);
                DWORD r= (y<<16)|x;
                SendMessage(m_gameHandle,WM_LBUTTONDOWN,1,r);
                SendMessage(m_gameHandle,WM_LBUTTONUP,1,r);
                haveNotMine=true;
            }
        }
    }
    //SetCursorPos(p.x,p.y);
    return haveNotMine;
}
void XpAdapter::clickPiece(pair<int,int> &minOne)
{
    int x = firstClick.first +minOne.first *16;
    int y=firstClick.second +minOne.second *16;
    DWORD r=(y<<16) | x;
    SendMessage(m_gameHandle,WM_LBUTTONDOWN,1,r);
    SendMessage(m_gameHandle,WM_LBUTTONUP,1,r);
}