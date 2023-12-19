// InputKeyNDot.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

#define BG_GRAY		BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE
#define FG_GRAY		FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
#define BG_WHITE		BG_GRAY|BACKGROUND_INTENSITY
#define FG_WHITE		FG_GRAY|FOREGROUND_INTENSITY
#define BG_BLACK		0
#define FG_BLACK		0
#define BG_DYELLOW	BACKGROUND_RED  |BACKGROUND_GREEN
#define BG_DPINK		BACKGROUND_RED  |BACKGROUND_BLUE
#define BG_DGREEN	BACKGROUND_GREEN|BACKGROUND_BLUE
#define FG_DYELLOW	FOREGROUND_RED  |FOREGROUND_GREEN
#define FG_DPINK		FOREGROUND_RED  |FOREGROUND_BLUE
#define FG_DGREEN	FOREGROUND_GREEN|FOREGROUND_BLUE
#define BG_YELLOW	BG_DYELLOW	|BACKGROUND_INTENSITY
#define BG_PINK		BG_DPINK	|BACKGROUND_INTENSITY
#define BG_LDGREEN	BG_DGREEN	|BACKGROUND_INTENSITY
#define FG_YELLOW	FG_DYELLOW	|FOREGROUND_INTENSITY
#define FG_PINK		FG_DPINK	|FOREGROUND_INTENSITY
#define FG_LDGREEN	FG_DGREEN	|FOREGROUND_INTENSITY
#define BG_RED		BACKGROUND_RED   
#define BG_GREEN		BACKGROUND_GREEN 
#define BG_BLUE		BACKGROUND_BLUE  
#define BG_LRED		BG_RED   |BACKGROUND_INTENSITY
#define BG_LGREEN	BG_GREEN |BACKGROUND_INTENSITY
#define BG_LBLUE		BG_BLUE  |BACKGROUND_INTENSITY
#define FG_RED		FOREGROUND_RED	 
#define FG_GREEN		FOREGROUND_GREEN 
#define FG_BLUE		FOREGROUND_BLUE  
#define FG_LRED		FG_RED	 |FOREGROUND_INTENSITY
#define FG_LGREEN	FG_GREEN |FOREGROUND_INTENSITY
#define FG_LBLUE		FG_BLUE  |FOREGROUND_INTENSITY
#define BG_INTENSITY	BACKGROUND_INTENSITY
#define FG_INTENSITY	FOREGROUND_INTENSITY

void KeyBoard(bool* playing, int puzzle[5][5],int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

// 게임 함수들
void InitPuzzle(int puzzle[5][5]);
void Print(HANDLE hOP, int puzzle[5][5], int x, int y); //화면에 퍼즐을 그려주는 함수
void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color);//퍼즐을 블럭별로 그려주는 함수
void Swap(int* prevBlock, int* currBlock);
bool Check(int puzzle[5][5]);

int main(){
    system("mode con:lines=25 cols=48");//lines 세로 cols 가로
 
    srand(time(NULL));
    rand();

    HANDLE hOP; // 핸들 값 가져오기(구조체인가?) //핸들: 전체 프로그램을 관리
    hOP = GetStdHandle(STD_OUTPUT_HANDLE);

    //커서 숨기기
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.bVisible = false;
    curInfo.dwSize = 1;
    SetConsoleCursorInfo(hOP, &curInfo);

    bool isPlaying = true;
    int nPuzzle[5][5];
    int nX = 4, nY = 4; //처음 빈 칸의 인덱스 번호

    InitPuzzle(nPuzzle);
    Print(hOP, nPuzzle, nX, nY);

    while (isPlaying) {
        if (_kbhit()) {//키 버퍼 확인: 키 입력이 있는 경우 버퍼에 값이 생겨서 true가 반환 된다.
           
            system("cls");

            KeyBoard(&isPlaying, nPuzzle, &nX, &nY);
            Print(hOP, nPuzzle, nX, nY);
            isPlaying = !Check(nPuzzle);
            
            if (isPlaying == false) {
                cout << "게임 클리어~! 게임을 종료합니다." << endl;
                system("pause");
            }

            while (_kbhit()) _getch();//버퍼의 값 지움
        }
    }
    
    
    return 0;

}


void KeyBoard(bool* playing, int puzzle[5][5], int* x, int* y){
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && *x < 4)
    {
        Swap(&puzzle[*y][*x], &puzzle[*y][*x + 1]);
        (*x)++;
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && *x > 0)
    {
        Swap(&puzzle[*y][*x], &puzzle[*y][*x - 1]);
        (*x)--;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000 && *y >0)
    {
        Swap(&puzzle[*y][*x], &puzzle[*y-1][*x]);
        (*y)--;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && *y < 4)
    {
        Swap(&puzzle[*y][*x], &puzzle[*y+1][*x]);
        (*y)++;
    }
    else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//ESC
        *playing = false;
}


void Draw(HANDLE hOP, int x, int y, char* str, WORD color){
    DWORD dwCharsWritten;
    COORD cdFill = { x, y };

    FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
    WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);

} 

void InitPuzzle(int puzzle[5][5]){
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            puzzle[i][j] = i * 5 + j+1;
    }
    //0=빈칸

    /*puzzle[0][0] = 24;
    puzzle[4][4] = 0;*/

    for (int i = 0; i < 1000; i++) {//짝수번 스왑해야 함.
        int nDestX = rand() % 5;
        int nDestY = rand() % 5;

        int nSrcX = rand() % 5;
        int nSrcY = rand() % 5;

        if ((nDestX == 4 && nDestY == 4) || (nSrcX == 4 && nSrcY == 4) ||
            (nDestX == nSrcX && nDestY == nSrcY))
        {
            i--;
            continue;
        }

        int nTemp = puzzle[nDestY][nDestX];
        puzzle[nDestY][nDestX] = puzzle[nSrcY][nSrcX];
        puzzle[nSrcY][nSrcX] = nTemp;
    }
}

void Print(HANDLE hOP, int puzzle[5][5], int x, int y) {
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            char* szTemp = new char;

            if (j == x && i == y)
                DrawBlock(hOP, 10 + j * 6,5+i*3, (char*)"■", BG_WHITE | FG_BLACK);
            else
                DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j], szTemp, 10), BG_WHITE | FG_BLACK);

        }

    }

  
}

void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color) {
    Draw(hOP, x + 0, y + 0, str, color);
    Draw(hOP, x + 2, y + 0, (char*)"■", color);
    Draw(hOP, x + 0, y + 1, (char*)"■", color);
    Draw(hOP, x + 2, y + 1, (char*)"■", color);
}


void Swap(int* prevBlock, int* currBlock) {

    int ntemp = *prevBlock;
    *prevBlock = *currBlock;
    *currBlock = ntemp;

}

bool Check(int puzzle[5][5]) {
    bool isComplete = false;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == 4 && j == 4)
                isComplete = true;
            if (puzzle[i][j] != i * 5 + j + 1)
                break;

        }
    }

    return isComplete;
}