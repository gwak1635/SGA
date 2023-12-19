// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

void Keyboard(bool* playing, int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

int main()
{
    HANDLE hOP; // 핸들 값 가져오기 (프로그램을 전체적으로 관리)
    hOP = GetStdHandle(STD_OUTPUT_HANDLE);

    //커서 숨기기
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.bVisible = false;
    curInfo.dwSize = 1;
    SetConsoleCursorInfo(hOP, &curInfo);

    bool isPlaying = true;
    int x = 10, y = 10;

    cout << "x좌표 : " << x << endl;
    cout << "y좌표 : " << y << endl;
    Draw(hOP, x*2, y, (char*)"A", BACKGROUND_RED);

    while (isPlaying) 
    {
        if (_kbhit())       //키 버퍼 확인: 키 입력이 있는 경우 버퍼에 값이 생겨서 true가 반환된다.
        {
            Keyboard(&isPlaying, &x, &y);//키보드 함수 호출

            system("cls");
            cout << "x좌표 : " << x << endl;
            cout << "y좌표 : " << y << endl;
            Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);
            while ((_kbhit()))
                _getch(); //버퍼에 남은 값을 제거하기
            //이 함수는 입력된 키보드 값을 변수로 저장함. ex): keyValue = getch();
        }
    }

    return 0;
}

void Keyboard(bool* playing, int* x, int* y) {
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        (*x)++;
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        (*x)--;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000) {
        (*y)--;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        (*y)++;
    }
    else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        *playing = false;
    }
}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color)//글자와 배경을 특수 위치에 써 줌
{
    DWORD dwCharsWritten;
    COORD cdFill = { x,y };

    FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);//색상을 칠해줌
    WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
}