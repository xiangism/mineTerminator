// mineTerminator.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "mineTerminator.h"
#include "GamePanel.h"
#include <CommCtrl.h>
#include <shellapi.h>
#include <shangjing/windows/image.hpp>
#include <shangjing/image/imageio.hpp>

//#pragma comment(lib,"comctl32.lib");

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
GamePanel gamePanel;
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DialogMain(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK  AboutProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    hInst = hInstance;
    DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG_main),NULL,DialogMain);
    return 0;
}

INT_PTR CALLBACK DialogMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
            HICON  hIcon=LoadIcon(hInst,(LPCTSTR)IDI_mine);
            SetClassLong(hDlg,GCL_HICON,(LONG)hIcon);
            RegisterHotKey(hDlg,100,0,VK_F4);
            RegisterHotKey(hDlg,101,0,VK_F3);
            return (INT_PTR)TRUE;
        }
        //case WM_INIT

    case WM_COMMAND:
        {
            WORD id=LOWORD(wParam) ;
            if (id == ID_run  )
            {
                gamePanel.allRun();
            } 
            else if(id==IDC_semiRun)
            {
                gamePanel.semiRun();
            }
            else if(id == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            else if(id==IDC_BUTTON_about)
            {
                DialogBox(hInst,MAKEINTRESOURCE(IDD_Dialog_About),hDlg,AboutProc);
                //DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG_main),hDlg,DialogMain);

            }
            break;
        }

    case WM_HOTKEY:
        {
            if(wParam==100)
                gamePanel.allRun();
            else if(wParam==101)
            {
                gamePanel.semiRun();
            }
            break;
        } 
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
            const TCHAR ch[]=_T("本软件实现了快速完成windows下扫雷游戏的功能\r\n")
                _T("现只适用于windows XP系统自带的winmine游戏\r\n")
                _T("半自动,只有在局面上出现可以判断的情况下才会点击，在这种模式下本程序不会点到雷\r\n")
                _T("全自动,当出现死局时,本程序会计算一个最不可能是雷的块，并点击。这种情况下本程序会点到雷")
                ;
            HWND h= GetDlgItem(hDlg,IDC_EDIT_describe);
            SendMessage(h,WM_SETTEXT,0,(WPARAM)ch);
            return (INT_PTR)TRUE;
        }
    case WM_COMMAND:
        {
            WORD id=LOWORD(wParam);
            if(id==IDOK ||id==IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
    case WM_NOTIFY:
        {
            WORD id=LOWORD(wParam);
            if(id==IDC_SYSLINK_web)
            {
                LPNMHDR lp=(LPNMHDR)lParam;
                if(lp->code==NM_CLICK)
                {
                    ShellExecute(NULL, _T("open"), _T("http://www.cnblogs.com/xiangism"),NULL,NULL, SW_SHOWNORMAL);
                }
            }
            break;
        }
    }
    return 0;
}
