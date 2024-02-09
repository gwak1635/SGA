// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//전역 디파인
#define WINSIZEX 640
#define WINSIZEY 720

#define PROGRAM_TITLE L"게임을 만들어 보자!"

//전역 매크로
// 렉트 생성 매크로 (x좌표, y좌표, 사이즈)
#define RECT_MAKE(x, y, s) { x - s / 2, y - s / 2, x + s / 2, y + s / 2 }
// 렉트 렌더 매크로
#define RECT_DRAW(rt) Rectangle(g_hDC, rt.left, rt.top, rt.right, rt.bottom)

//전역 변수(extern: 외부에서 접근 가능하게 연결하는 것)
extern HWND		g_hWnd;										// 윈도우 핸들
extern POINT	g_ptMouse;
extern HDC		g_hDC;

//문자열 " "
//문자열 L" " : 한글과 같은 멀티바이트를 사용하여 표현되는 문자를 표시

#include <string>
#include <time.h>
#include <vector>

using namespace std;

#include "MainGame.h"