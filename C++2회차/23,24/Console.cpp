// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

void Keyboard(bool* playing,int puzzle[5][5], int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

// 게임 함수들
void InitPuzzle(int puzzle[5][5]); //퍼즐 초기화 함수 및 셔플
void Print(HANDLE hOP, int puzzle[5][5], int x, int y);//퍼즐을 그려주는 함수
void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color);//퍼즐을 블럭별로 그려주는 함수

void Swap(int* prevBlock, int* currBlock);
bool Check(int puzzle[5][5]);

int main()
{
    system("mode con:lines=25 cols=48"); //콘솔창의 가로 세로크기 지정
    //lines: 세로, cols: 가로


    srand(time(NULL));
    rand();

    HANDLE hOP; // 핸들 값 가져오기 (프로그램을 전체적으로 관리)
    hOP = GetStdHandle(STD_OUTPUT_HANDLE);

    //커서 숨기기
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.bVisible = false;
    curInfo.dwSize = 1;
    SetConsoleCursorInfo(hOP, &curInfo);

    bool isPlaying = true;
    int nPuzzle[5][5];
    int nX = 4, nY = 4;//처음 빈칸의 인덱스 번호

    InitPuzzle(nPuzzle);
    Print(hOP, nPuzzle, nX, nY);

    while (isPlaying) 
    {
        if (_kbhit())       //키 버퍼 확인: 키 입력이 있는 경우 버퍼에 값이 생겨서 true가 반환된다.
        {

            system("cls");
            
            Keyboard(&isPlaying, nPuzzle, &nX, &nY);
            Print(hOP, nPuzzle, nX, nY);
            isPlaying = !Check(nPuzzle);

            if (isPlaying == false)
            {
                cout << "게임 클리어! 게임을 종료합니다." << endl;
                system("pause");
            }

            while ((_kbhit()))
                _getch(); //버퍼에 남은 값을 제거하기
            //이 함수는 입력된 키보드 값을 변수로 저장함. ex): keyValue = getch();
        }
    }

    return 0;
}

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y) {
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && *x <4) 
    {
        Swap(&puzzle[*y][*x], &puzzle[*y][*x + 1]);
        (*x)++;
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && *x >0) {
        Swap(&puzzle[*y][*x], &puzzle[*y][*x -1]);
        (*x)--;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000 && *y > 0) {
        Swap(&puzzle[*y][*x], &puzzle[*y-1][*x]);
        (*y)--;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && *y < 4) {
        Swap(&puzzle[*y][*x], &puzzle[*y + 1][*x]);
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

void InitPuzzle(int puzzle[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            puzzle[i][j] = i * 5 + j;
        }
    }

    //24, 0 스왑
    puzzle[0][0] = 24;
    puzzle[4][4] = 0;

    //스왑 횟수는 짝수여야 정상적으로 실행됨. 앞서 1번 스왑했으므로 홀수 번 스왑.
    for (int i = 0; i < 999; i++)
    {
        int nDestX = rand() % 5;
        int nDestY = rand() % 5;
        
        int nSrcX = rand() % 5;
        int nSrcY = rand() % 5;

        if ((nDestX == 4 && nDestY == 4) || (nSrcX == 4 && nSrcY == 4) ||
            (nDestX == nSrcX && nDestY == nSrcY)) //실제로 스왑을 실행하지 않는 경우 i--로 i++를 상쇄함.
        {
            i--;
            continue;
        }

        int nTemp = puzzle[nDestX][nDestY];
        puzzle[nDestX][nDestY] = puzzle[nSrcX][nSrcY];
        puzzle[nSrcX][nSrcY] = nTemp;
          
    }

}

void Print(HANDLE hOP, int puzzle[5][5], int x, int y)//퍼즐을 그려주는 함수
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            char* szTemp = new char;
            //itoa : 정수값을 문자로 변환해주는 함수

            if (i == y && j == x)//빈칸 블럭
            {
                DrawBlock(hOP, 10 + j * 6, 5 + i * 3, (char*)"■", BG_WHITE | FG_BLACK);
            }
            else
            {
                DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j], szTemp, 10), BG_WHITE | FG_BLACK);
            }
        }
    }
}

void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color)//퍼즐을 블럭별로 그려주는 함수
{
    Draw(hOP, x + 0, y + 0, str, color);
    Draw(hOP, x + 2, y + 0, (char*)"■", color);
    Draw(hOP, x + 0, y + 1, (char*)"■", color);
    Draw(hOP, x + 2, y + 1, (char*)"■", color);
}

void Swap(int* prevBlock, int* currBlock) {
    int nTemp = *prevBlock;
    *prevBlock = *currBlock;
    *currBlock = nTemp;
}

bool Check(int puzzle[5][5]) {

    bool isComplete = false;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == 4 && j == 4)
                isComplete = true;


            if (puzzle[i][j] != j +1 +i * 5)
                break;
            
            

            
        }
    }

    return isComplete;
}