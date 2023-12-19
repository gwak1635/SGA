// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

/*
Windowa Application Program Interface (WinAPI)
Windows : 운영체제 (OS, Operating System)
API : 운영체제가제공하는 함수의 집합체

핸들의 정의: 운영체제 내부에 있는 리소스의 주소를 정수로 치환한 값

Resouce : 각종 하드웨어 장치 또는 저장장치에 들어있는 데이터 자료

Instance Handle : 윈도우에서 현재 실행중인 프로세서 핸들을 가리키는 용어

*/



#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND    g_hWnd;                                 // 윈도우 핸들 
WCHAR szTitle[MAX_LOADSTRING] = PROGRAM_TITLE;  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

POINT ptPos{ 0,0 };//조작할 렉트의 좌표값
// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                 MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,   //프로그램의 핸들 인스턴스
                     _In_opt_ HINSTANCE hPrevInstance, //이전에 실행된 핸들 인스턴스(사용 안함)
                     _In_ LPWSTR    lpCmdLine,// 명령행으로 입력된 프로그램 인수
                     _In_ int       nCmdShow)// 프로그램이 시작되 때 형태 (최소화, 보통 등의 상태값)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    //엑셀러레이터(단축키) 테이블을 읽어들인다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //키보드 메시지를 WM_COMMAND(윈도우 메세지 명령어)로 변경해서 엑셀러레이터가 동작할 수 있도록 해주는 함수
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;       // WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX); // 구조체의 크기 정보

    wcex.style          = CS_HREDRAW | CS_VREDRAW;                                          //윈도우 스타일 (창의 크기 변경 시 창을 다시 그린다.
    wcex.lpfnWndProc    = WndProc;                                                          //윈도우 프로시져(메시지 처리 함수)
    wcex.cbClsExtra     = 0;                                                                //클래스 여분의 메모리
    wcex.cbWndExtra     = 0;                                                                //윈도우 여분의 메모리
    wcex.hInstance      = hInstance;                                                        //인스턴스
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));        //아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                                   //커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                                         //화면 색상
    wcex.lpszMenuName   = NULL;                                                               //메뉴 이름 (NULL-> 메뉴 없앰)
    wcex.lpszClassName  = szWindowClass;                                                    //클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));             //작은 아이콘

    return RegisterClassExW(&wcex);
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
       szWindowClass, // 윈도우 클래스 이름
       szTitle, //타이틀바에 띄울 이름
       WS_OVERLAPPEDWINDOW, //윈도우 스타일
       nWinPosX,// 윈도우 화면 좌표 X
       nWinPosY,//윈도우 화면 좌표 Y
       WINSIZEX, // 윈도우 가로 사이즈
       WINSIZEY,// 윈도우 세로 사이즈
       nullptr,// 부모 윈도우
       nullptr,// 메뉴 핸들
       hInstance, // 인스턴스 지정
       nullptr); //자식 윈도우를 생성하면 지정 그렇지 않으면 NULL

   if (!hWnd)
   {
      return FALSE;
   }
   
   g_hWnd = hWnd;

   // 윈도우 사이즈 조정 (타이틀 바 및 메뉴 사이즈 실 사이즈에서 제외)
   RECT rt = { nWinPosX, nWinPosY, nWinPosX + WINSIZEX, nWinPosY + WINSIZEY };
   AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
   MoveWindow(hWnd, nWinPosX, nWinPosY, rt.right - rt.left, rt.bottom - rt.top, TRUE);
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
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
    case WM_CREATE: // 프로그램이 실행될때 한번 호출된다.(초기화)
        SetTimer(hWnd, 1, 10, NULL);//(핸들, 타이머의 번호, 호출 주기(ms), NULL로 세팅 시 WM_TIMER 호출)
        break;
    case WM_TIMER: //타이머에 의해서 호출됨
        InvalidateRect(hWnd, NULL, true); //(핸들, 영역, 새로쓰기)
        break;
    case WM_KEYDOWN: // 키 입력이 있을 때마다 호출된다.
        switch (wParam)
        {
            
        case 'A': case VK_LEFT:// 조건문의 or연산
            ptPos.x -= (ptPos.x > 0) ? 1 : -15;
            break;
        case 'D': case VK_RIGHT:
            ptPos.x += (ptPos.x < 15) ? 1 : -15;
            break;
        case 'W': case VK_UP:
            ptPos.y -= (ptPos.y > 0)  ? 1 : -8;
            break;
        case 'S': case VK_DOWN:
            ptPos.y += (ptPos.y < 8 ) ? 1 : -8;
            break;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            //dc handle: Device Context(출력을 위한 모든 데이터를 가지는 구조체)  Handle
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            //wstring wstr = L"코딩 지옥으로 입장을 허가 합니다!!";//멀티바이트라 wstring
            //TextOut(hdc, 10, 10, wstr.c_str(), wstr.length());

            //MoveToEx(hdc, 20, 20, NULL);
            //LineTo(hdc, 50, 50);
            //LineTo(hdc, 100, 50);

            //Rectangle(hdc, 200, 200, 300, 300);

            //Ellipse(hdc, 400, 400, 500, 500);

            int roomsize = WINSIZEY/9;

            for (int i = 0; i < WINSIZEX; i+= WINSIZEY / 9)
            {
                MoveToEx(hdc, i, 0, NULL);
                LineTo(hdc, i, WINSIZEY);
            }
            for (int i = 0; i < WINSIZEY; i += WINSIZEX / 16)
            {
                MoveToEx(hdc, 0, i, NULL);
                LineTo(hdc, WINSIZEX, i);
            }

            int ptX = ptPos.x * roomsize;
            int ptY = ptPos.y * roomsize;


            Rectangle(hdc, ptX+10, ptY+10, ptX + roomsize - 10, ptY + roomsize - 10);
          

            EndPaint(hWnd, &ps);
        }
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
