#include "stdafx.h"
#include "AdapterGame.h"

AdapterGame::AdapterGame()
{

}

AdapterGame::~AdapterGame()
{

}

void AdapterGame::findGameWindow()
{
    m_gameHandle=FindWindow(NULL,L"É¨À×");

    if(m_gameHandle)
    {
        GetWindowRect(m_gameHandle,&m_gameRect);
        //moveShowWindow();
        //GetWindowRect(m_gameHandle,&m_gameRect);
        m_gameType=getGameType();
    }

}

void AdapterGame::moveShowWindow()
{
    ShowWindow(m_gameHandle,SW_SHOWMINIMIZED);
    ShowWindow(m_gameHandle,SW_SHOWNORMAL);
    int screenWith= GetSystemMetrics(SM_CXFULLSCREEN);
    int screenHeigh= GetSystemMetrics(SM_CYFULLSCREEN);
    int width= m_gameRect.right-m_gameRect.left;
    int height=m_gameRect.bottom-m_gameRect.top;
    //if(m_gameRect.left<0)
    //{
    //    MoveWindow(m_gameHandle,0,m_gameRect.top,width,height,true);
    //    return;
    //}
    //if(m_gameRect.top<0)
    //{
    //    MoveWindow(m_gameHandle,m_gameRect.left,0,width,height,true);
    //    return;
    //}
    //if (m_gameRect.right > screenWith)
    //{
    //    MoveWindow(m_gameHandle,screenWith-width,m_gameRect.top,width,height,true);
    //    return;
    //}
    //if(m_gameRect.bottom>screenHeigh)
    //{
    //    MoveWindow(m_gameHandle,m_gameRect.left,screenHeigh-height,width,height,true);
    //    return;
    //}
}