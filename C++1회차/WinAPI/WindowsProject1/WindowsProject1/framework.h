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

// 전역 디파인
#define WINSIZEX 1280
#define WINSIZEY 720

#define PROGRAM_TITLE L"게임을 만들어 보자!!"

// 문자열 L" " : 한글과 같은 멅바이트를 사용하여 표현되는 문자를 표시

#include <string>

using namespace std;