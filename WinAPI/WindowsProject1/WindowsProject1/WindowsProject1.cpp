﻿// WindowsProject1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

/*
Windows Application Program Interface (WinAPI)
Windows : 운영체제 (OS, Operating System)
API : 운영체제가 제공하는 함수의 집합체

핸들의 정의 : 운영체제 내부에 있는 리소스(자원)의 주소를 정수로 치환한 값
            리소스의 주소와 함게 핸들 테이블에서 관리 된다.

Resouce : 각종 하드웨어 장치 또는 저장장치(메모리, 하드 등)에 들어있는 데이터 자료

Instance Handle : 윈도우에서 현재 실행중인 프로세서 핸들을 가리키는 용어
*/

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE	hInst;										// 현재 인스턴스입니다.
WCHAR		szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;	// 제목 표시줄 텍스트입니다.
WCHAR		szWindowClass[MAX_LOADSTRING];				// 기본 창 클래스 이름입니다.

HWND		    g_hWnd;										// 윈도우 핸들
POINT			g_ptMouse;
HDC             g_hDC;

MainGame*       pMainGame=NULL;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// 프로그램의 핸들 인스턴스
    _In_opt_ HINSTANCE hPrevInstance,	// 이전에 실행 된 핸들 인스턴스(사용 안함)
    _In_ LPWSTR    lpCmdLine,			// 명령행으로 입력 된 프로그램 인수
    _In_ int       nCmdShow)			// 프로그램이 시작 될 때 형태 (최소화, 보통 등의 상태값)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);

    // 창 클래스 등록
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow)) // InitInstance (hInstance, nCmdShow) == FALSE
    {
        return FALSE;
    }

    // 엑셀러레이터(단축키) 테이블을 읽어드린다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    HDC hdc = GetDC(g_hWnd);
    g_hDC = CreateCompatibleDC(hdc);                                            //화면에 출력되지 않는 비트맵 객체를 연결할 수 있는 DC
    HBITMAP hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY); //렌더할 비트맵 생성
    SelectObject(g_hDC, hBitmap);                                               // 생성한 비트맵을 백버퍼 DC에 연결

    pMainGame = new MainGame;    //할당
    pMainGame->Init();

    MSG msg;

    // 기본 메시지 루프입니다:

    //메세지가 없는 시간을 데스 타임이라고 부름(대기하다 CPU 성능 버림)
    //픽 메시지 루프
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            if (pMainGame) {
                pMainGame->Update();
                pMainGame->Render();
            }
        }
    }
    delete pMainGame;       //해제

    DeleteObject(hBitmap);
    DeleteDC(g_hDC);

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;		// WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);													// 구조체의 크기 정보

    wcex.style = CS_HREDRAW | CS_VREDRAW;										// 윈도우 스타일
    wcex.lpfnWndProc = WndProc;														// 윈도우 프로시져 (메시지 처리 함수)
    wcex.cbClsExtra = 0;															// 클래스 여분의 메모리
    wcex.cbWndExtra = 0;															// 윈도우 여분의 메모리
    wcex.hInstance = hInstance;													// 인스턴스
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));	// 아이콘
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);								// 커서
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);										// 백그라운드
    wcex.lpszMenuName = NULL;															// 메뉴 이름 (NULL 메뉴 없앰)
    wcex.lpszClassName = szWindowClass;												// 클래스 이름
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));			// 작은 아이콘

    return RegisterClassExW(&wcex);	// 윈도우 클래스 등록
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 화면 해상도 얻기
    int nResolutionX = GetSystemMetrics(SM_CXSCREEN);
    int nResolutionY = GetSystemMetrics(SM_CYSCREEN);

    // 창 화면 중앙 위치 계산
    int nWinPosX = nResolutionX / 2 - WINSIZEX / 2;
    int nWinPosY = nResolutionY / 2 - WINSIZEY / 2;

    HWND hWnd = CreateWindowW(
        szWindowClass,			// 윈도우 클래스 이름
        szTitle,					// 타이틀바에 띠울 이름
        WS_OVERLAPPEDWINDOW,		// 윈도우 스타일
        nWinPosX,				// 윈도우 화면 좌표 x
        100,						// 윈도우 화면 좌표 y
        WINSIZEX,				// 윈도우 가로 사이즈
        WINSIZEY,				// 윈도우 세로 사이즈
        nullptr,					// 부모 윈도우
        nullptr,					// 메뉴 핸들
        hInstance,				// 인스턴스 지정
        nullptr					// 자식 윈도우를 생성하면 지정 그렇지 않으면 NULL
    );

    if (!hWnd)
    {
        return FALSE;
    }

    g_hWnd = hWnd;

    // 윈도우 사이즈 조정 (타이틀 바 및 메뉴 사이즈 실 사이즈에서 제외)
    RECT rt = { nWinPosX, nWinPosY, nWinPosX + WINSIZEX, nWinPosY + WINSIZEY };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    MoveWindow(hWnd, nWinPosX, 100, rt.right - rt.left, rt.bottom - rt.top, TRUE);

    ShowWindow(hWnd, nCmdShow);	// 화면에 창을 보여준다.
    UpdateWindow(hWnd);			// 창 업데이트

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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
    case WM_MOUSEMOVE:
        g_ptMouse.x = LOWORD(lParam);
        g_ptMouse.y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
