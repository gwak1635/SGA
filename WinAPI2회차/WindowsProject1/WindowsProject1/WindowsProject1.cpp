// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE   hInst;                                      // 현재 인스턴스입니다.
HWND        g_hWnd;                                      // 윈도우 핸들
WCHAR       szTitle[MAX_LOADSTRING]=PROGRAM_TITLE;      // 제목 표시줄 텍스트입니다.
WCHAR       szWindowClass[MAX_LOADSTRING];              // 기본 창 클래스 이름입니다.

enum MOVE_DIR {MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN};
//렉트 생성 매크로(x,y, 사이즈)
#define RECT_MAKE(x,y,s) {x-s/2,y-s/2,x+s/2,y+s/2}//매크로는 세미콜론 안붙임
//렉트 렌더 매크로
#define RECT_DRAW(rt) Rectangle(hdc,rt.left,rt.top,rt.right,rt.bottom)

POINT       ptPos1 = { 100,100 }; //조작할 렉트의 좌표값
RECT        rtBox1;
MOVE_DIR    eMoveDir;
float       fMoveSpeed = 20;

POINT       ptPos2 = { WINSIZEX / 2.0f,WINSIZEY / 2.0f };//충돌 대상 렉트의 좌표값
RECT        rtBox2;

POINT       ptMouse;
bool        isPicked = false;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//WinAPI의 메인함수!
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         //핸들 인스턴스
                     _In_opt_ HINSTANCE hPrevInstance,//이전에 실행된 핸들 인스턴스(사용 안 함)
                     _In_ LPWSTR    lpCmdLine,//명령행으로 입력된 프로그램 인수
                     _In_ int       nCmdShow)//프로그램이 시작될 때의 형태(최소화, 보통 등의 상태값) 
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

    //단축키 테이블을 읽어들인다
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 키보드 메세지를 WM_COMMAND로 변경해서 단축키가 동작할 수 있도록 해주는 함수
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
    WNDCLASSEXW wcex;       //WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체

    wcex.cbSize = sizeof(WNDCLASSEX); //구조체의 크기 정보

    wcex.style          = CS_HREDRAW | CS_VREDRAW;  //윈도우 스타일
    wcex.lpfnWndProc    = WndProc;                  //윈도우 프로시저(메시지 처리 함수)
    wcex.cbClsExtra     = 0;                        //클래스 여분의 메모리
    wcex.cbWndExtra     = 0;                        //윈도우 여분의 메모리
    wcex.hInstance      = hInstance;                //핸들 인스턴스
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));//아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                           //커서
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                                 //백그라운드(브러시 색상 등)
    wcex.lpszMenuName   = NULL;                                        //메뉴 이름
    wcex.lpszClassName  = szWindowClass;                                             //클래스 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));     //작은 아이콘

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

   //화면 해상도 얻기
   int nResolutionX = GetSystemMetrics(SM_CXSCREEN);
   int nResolutionY = GetSystemMetrics(SM_CYSCREEN);

   //창 화면 중앙 위치 계산
   int nWinPosX = nResolutionX / 2 - WINSIZEX / 2;
   int nWinPosY = (nResolutionY - WINSIZEY) / 2;

   HWND hWnd = CreateWindowW(
       szWindowClass,           //윈도우 클래스 이름
       szTitle,                 //타이틀바에 띄울 이름
       WS_OVERLAPPEDWINDOW,     //윈도우 스타일(최소화, 보통 등)
       nWinPosX,                //화면 좌표 x
       100,                       //화면 좌표 y
       WINSIZEX,                //가로 사이즈
       WINSIZEY,                //세로 사이즈
       nullptr,                 //부모 윈도우
       nullptr,                 //메뉴 핸들
       hInstance,               //인스턴스 지정
       nullptr                  //자식 윈도우를 생성하면 지정 그렇지 않으면 NULL
   );

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   //윈도우 사이즈 조정(타이틀 바 및 메뉴 사이즈 실 사이즈에서 제외)
   RECT rt = { nWinPosX,nWinPosY,nWinPosX + WINSIZEX,nWinPosY + WINSIZEY };
   AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
   MoveWindow(hWnd, nWinPosX, 100, rt.right - rt.left, rt.bottom-rt.top, TRUE);
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
    case WM_CREATE:// 프로그램이 실행될 때 한번 호출된다.
        SetTimer(hWnd, 1, 10, NULL);//핸들, 타이머 이름, 간격(1초에 n번)
        break;
    case WM_TIMER: //타이머에 의해서 호출
        InvalidateRect(hWnd, NULL, true);//전체영역 다시그림
        
        rtBox1 = RECT_MAKE(ptPos1.x, ptPos1.y, 100);
        rtBox2 = RECT_MAKE(ptPos2.x, ptPos2.y, 100);
        
        if (isPicked) {
            ptPos2 = ptMouse;
        }
        break;
    case WM_KEYDOWN://키 입력이 있을 때마다 호출된다.
        switch (wParam) {
        case 'A': case VK_LEFT:
            ptPos1.x -= (rtBox1.left >= fMoveSpeed)? fMoveSpeed : 0;
            eMoveDir = MOVE_LEFT;
            break;
        case 'D': case VK_RIGHT:
            ptPos1.x+= (rtBox1.right <= WINSIZEX-fMoveSpeed) ? fMoveSpeed :0;
            eMoveDir = MOVE_RIGHT;
            break;
        case 'W': case VK_UP:
            ptPos1.y-= (rtBox1.top >= fMoveSpeed) ? fMoveSpeed : 0;
            eMoveDir = MOVE_UP;
            break;
        case 'S': case VK_DOWN:
            ptPos1.y+= (rtBox1.bottom <= WINSIZEY - fMoveSpeed) ? fMoveSpeed : 0;
            eMoveDir = MOVE_DOWN;
            break;
        }
    case WM_MOUSEMOVE:
        ptMouse.x = LOWORD(lParam);//마우스 포인터 값을 불러오는  파라메터
        ptMouse.y = HIWORD(lParam);
        break;
    case WM_LBUTTONDOWN:
        if (PtInRect(&rtBox2, ptMouse))
        {
            ptPos2 = ptMouse;
            isPicked = true;
        }
        break;
    case WM_LBUTTONUP:
        isPicked = false;
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        //Device Context: 출력을 위한 모든 데이터를 가지는 구조체
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        //포지션 위치에 따른 렉트 정보 업데이트
        RECT_DRAW(rtBox1);
        RECT_DRAW(rtBox2);
        
        RECT rt;
        if (IntersectRect(&rt, &rtBox1, &rtBox2)) {
            switch (eMoveDir)
            {
            case MOVE_LEFT:
                ptPos2.x -= fMoveSpeed;
                break;
            case MOVE_RIGHT:
                ptPos2.x += fMoveSpeed;
                break;
            case MOVE_UP:
                ptPos2.y -= fMoveSpeed;
                break;
            case MOVE_DOWN:
                ptPos2.y += fMoveSpeed;
                break;
            }
        }

        EndPaint(hWnd, &ps);
        break;
        }
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
