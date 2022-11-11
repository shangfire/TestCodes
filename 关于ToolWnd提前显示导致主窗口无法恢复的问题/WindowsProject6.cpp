// WindowsProject6.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject6.h"
#include <string>
#include <format>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING] = L"classMain";            // 主窗口类名
WCHAR szWindowClass2[MAX_LOADSTRING] = L"classSub";            // 主窗口类名

HWND mainWnd;
HWND subWnd;
HWND hwd;

void syncMini() {
    if (::IsIconic(mainWnd)) {
        if (!::IsIconic(subWnd)) {
            ::SendMessage(subWnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
        }
    }
    else {
		if (::IsIconic(subWnd)) {
			::SendMessage(subWnd, WM_SYSCOMMAND, SC_RESTORE, NULL);
		}
    }
}

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                MyRegisterClass2(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc2(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINDOWSPROJECT6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    MyRegisterClass2(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT6));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEX);

    //wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    //wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT6));
    //wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT6);
    wcex.lpszClassName  = szWindowClass;
    //wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

ATOM MyRegisterClass2(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);

	//wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc2;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT6));
	//wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT6);
	wcex.lpszClassName = szWindowClass2;
	//wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   mainWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!mainWnd)
   {
      return FALSE;
   }

   ShowWindow(mainWnd, nCmdShow);
   UpdateWindow(mainWnd);

   subWnd = CreateWindowExW(WS_EX_TOOLWINDOW, szWindowClass2, szTitle, WS_OVERLAPPED,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, mainWnd, nullptr, hInst, nullptr);
   ShowWindow(subWnd, SW_SHOWNORMAL);
   UpdateWindow(subWnd);

   //::SetWindowPos(subWnd, NULL, -32000, -32000, 0, 0, SWP_NOACTIVATE | SWP_SHOWWINDOW);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//

#define WM_SSSS (WM_USER + 0x01)

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    ::OutputDebugString(std::format(L"\nWndProc:0x{:04X}", message).c_str());

    switch (message)
    {
	case WM_ERASEBKGND:
	case WM_PAINT:
	case WM_MOVE:
	//case WM_ACTIVATE:
	//case WM_NCACTIVATE:
    {
        if (message == WM_PAINT) {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			EndPaint(hWnd, &ps);
        }


        if (subWnd) {
			//if (::IsIconic(hWnd)) {
   //             ShowWindow(subWnd, SW_HIDE);
			//}
   //         else {
				RECT rect = { 0 };
				::GetClientRect(mainWnd, &rect);
				MapWindowPoints(mainWnd, HWND_DESKTOP, (POINT*)(&rect), 2);
				::SetWindowPos(subWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);
				::OutputDebugString(std::format(L"\nSetWindowPos:{:d},{:d},{:d},{:d}", rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top).c_str());
            //}
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hWnd, &ps);
	//	// TODO: 在此处添加使用 hdc 的任何绘图代码...
	//	EndPaint(hWnd, &ps);
	//}
	//break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SYSCOMMAND:
        if (wParam == SC_MINIMIZE) {
            ::OutputDebugString(L"\nasdasd");
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        else if (wParam == SC_CLOSE) {
            //::SetWindowPos(subWnd, NULL, 0, 0, 100, 100, SWP_NOACTIVATE | SWP_SHOWWINDOW);
            //::PostMessage(hWnd, WM_SSSS, NULL, NULL);
            ::MessageBox(subWnd, NULL, NULL, MB_OK);
            return 0;
        }
        else {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
		break;
    case WM_SSSS:
		::MessageBox(subWnd, NULL, NULL, MB_OK);
		return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_MINIMIZE) {
			::OutputDebugString(L"\nasdasd");
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		else if (wParam == SC_CLOSE) {
            

			::MessageBox(NULL, NULL, NULL, MB_OK);
			return 0;
		}
		else {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
