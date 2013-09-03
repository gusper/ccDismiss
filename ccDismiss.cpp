#include "stdafx.h"
#include "ccdismiss.h"
#include <regext.h>
#include "snapi.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE g_hInst;  // current instance
HWND	 g_hWndMenuBar;	// menu bar handle
HWND g_hWnd;
HREGNOTIFY g_hNotify = NULL;

// Forward declarations of functions included in this code module:
ATOM	 MyRegisterClass(HINSTANCE, LPTSTR);
BOOL	 InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow)) 
    {
        return FALSE;
    }

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//  PURPOSE: Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
    WNDCLASS wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHARGECOMPLETEDISABLER));
    wc.hCursor       = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = 0;
    wc.lpszClassName = szWindowClass;

    return RegisterClass(&wc);
}

//   PURPOSE: Saves instance handle and creates main window
//   COMMENTS:
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    TCHAR szTitle[MAX_LOADSTRING]; // title bar text
    TCHAR szWindowClass[MAX_LOADSTRING]; // main window class name

    g_hInst = hInstance; // Store instance handle in our global variable

    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the device specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_CHARGECOMPLETEDISABLER, szWindowClass, MAX_LOADSTRING);

    // If it is already running, then focus on the window, and exit
    g_hWnd = FindWindow(szWindowClass, szTitle);	
    if (g_hWnd) 
    {
        return FALSE;
    } 

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
        return FALSE;
    }

    g_hWnd = CreateWindow(szWindowClass, szTitle, NULL,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!g_hWnd)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK WindowSearcher(HWND hwnd, LPARAM lParam)
{
    TCHAR szTitle[MAX_LOADSTRING];
    wcscpy_s(szTitle, MAX_LOADSTRING, _T("Main Battery")); 

    // Since we know we're looking just for the "Main Battery" window,
    // we should only go further if the title is the same length
    int cTxtLen = GetWindowTextLength(hwnd); 
    if (cTxtLen != 12) 
        return TRUE;

    PTSTR pszMem = (PTSTR)VirtualAlloc((LPVOID) NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE); 
    if (pszMem != NULL)
    {
        GetWindowText(hwnd, pszMem, cTxtLen + 1); 

        if (wcsicmp(szTitle, pszMem) == 0)
        {
            VirtualFree(pszMem, (DWORD)(cTxtLen + 1), MEM_RELEASE);
            SendMessage(hwnd, WM_CLOSE, NULL, NULL);
            return FALSE;
        }
    }

    VirtualFree(pszMem, (DWORD)(cTxtLen + 1), MEM_RELEASE);

    return TRUE;
}

void FindAndCloseWindow()
{
    Sleep(5000);
    EnumWindows(WindowSearcher, NULL);
}

void RegistryNotifyCallbackFunc(HREGNOTIFY hNotify, DWORD dwUserData, const PBYTE pData, const UINT cbData)
{
    if (dwUserData == 100)
    {
        FindAndCloseWindow();
    }
}

void RegisterForNotification()
{
    NOTIFICATIONCONDITION nc;
    nc.dwMask = SN_POWERBATTERYSTRENGTH_BITMASK;
    nc.ctComparisonType = REG_CT_GREATER_OR_EQUAL;
    nc.TargetValue.dw = 0x51;

    RegistryNotifyCallback(SN_POWERBATTERYSTRENGTH_ROOT, SN_POWERBATTERYSTRENGTH_PATH, SN_POWERBATTERYSTRENGTH_VALUE, RegistryNotifyCallbackFunc, 100, &nc, &g_hNotify);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;

    switch (message) 
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam); 
        wmEvent = HIWORD(wParam); 

        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_OK:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;

    case WM_CREATE:
        SHMENUBARINFO mbi;

        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hWnd;
        mbi.nToolBarId = IDR_MENU;
        mbi.hInstRes   = g_hInst;

        if (!SHCreateMenuBar(&mbi)) 
        {
            g_hWndMenuBar = NULL;
        }
        else
        {
            g_hWndMenuBar = mbi.hwndMB;
        }

        RegisterForNotification();

        break;

    case WM_DESTROY:
        CommandBar_Destroy(g_hWndMenuBar);
        RegistryCloseNotification(g_hNotify);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}