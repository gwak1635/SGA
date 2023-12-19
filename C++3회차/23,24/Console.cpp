// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

//게임 함수들
void InitPuzzle(int puzzle[5][5]);								//퍼즐 초기화 함수
void PrintPuzzle(HANDLE hOP, int puzzle[5][5], int x, int y);	//화면에 퍼즐을 그려주는 함수
void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color);	//퍼즐을 블럭별로 그려주는 함수;

void Swap(int* prevBlock, int* currBlock);
bool Check(int puzzle[5][5]);

int main()
{
	system("mode con:lines=25 cols=48");//콘솔창의 가로세로 크기 지정

	srand(time(NULL));
	rand();

	HANDLE hOP; //핸들 값 가져오기[전체 프로그램 관리]
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);
    
	//커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	//게임 진행 변수
	bool isPlaying = true;
	int nPuzzle[5][5];
	int nX = 4, nY = 4;//처음 빈칸의 인덱스 번호

	InitPuzzle(nPuzzle);
	PrintPuzzle(hOP, nPuzzle, nX, nY);

	while (isPlaying) {

		if (_kbhit())//키 버퍼 확인 함수(bool형 반환)
		{
			system("cls");
			
			//대충 숫자 바꾸는 함수
			Keyboard(&isPlaying, nPuzzle, &nX, &nY);
			PrintPuzzle(hOP, nPuzzle, nX, nY);
			isPlaying = !Check(nPuzzle);
			//완료되었는지 확인하고 완료되었으면 게임 종료
			if (isPlaying == false) {
				cout << "퍼즐을 다 맞췄습니다! 게임 종료!" << endl;
				system("pause");
				
			}

			while (_kbhit()) _getch();//버퍼 비우기
			//이 함수는 입력된 키보드 값을 변수로 바로 저장할 때도 사용됨
			//nKeyValue = getch(); 
		}
	}

	return 0;
}

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y) {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && *x < 4) //오른쪽 방향키
	{
		Swap(&puzzle[*y][*x], &puzzle[*y][*x + 1]);
		(*x)++;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && *x > 0) //왼쪽 방향키
	{
		Swap(&puzzle[*y][*x], &puzzle[*y][*x - 1]);
		(*x)--;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000 && *y > 0) //위쪽 방향키
	{
		Swap(&puzzle[*y][*x], &puzzle[*y - 1][*x]);
		(*y)--;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && *y < 4) //아래쪽 방향키
	{
		Swap(&puzzle[*y][*x], &puzzle[*y + 1][*x]);
		(*y)++;
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) //아래쪽 방향키
		*playing = false;

}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color) {
	
	DWORD dwCharsWritten;
	COORD cdFill = { x,y };

	//색상을 칠해주는 함수
	FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	//문자를 적어주는 함수
	WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
}

void InitPuzzle(int puzzle[5][5]) {
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			puzzle[i][j] = i * 5 + j;
		}
	}

	puzzle[0][0] = 24;
	puzzle[4][4] = 0;//1회 스왑

	//짝수 회수 스왑해야 하나 1회 스왑하였으므로 홀수번 스왑
	for (int i = 0; i < 999; i++) {
		//24번 슬롯은 0으로 고정하기 위해 기피해 스왑
		int nSrc = rand() % 24;
		int nDest = rand() % 24;

		if (nSrc == nDest) {
			i--;//한번 더 섞게 하기
			continue;//아래쪽은 실행하지 않고 다시 위로 올라감
		}

		int nTemp = puzzle[nSrc / 5][nSrc % 5];
		puzzle[nSrc / 5][nSrc % 5] = puzzle[nDest / 5][nDest % 5];
		puzzle[nDest / 5][nDest % 5] = nTemp;
	}
}


void PrintPuzzle(HANDLE hOP, int puzzle[5][5], int x, int y) {
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			char* szTemp = new char;

			if (j == x && i == y) {
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, (char*)"■", BG_WHITE|FG_BLACK);
			}
			else
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j], szTemp, 10), BG_WHITE | FG_BLACK);
		}
	}
}

void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color) {
	Draw(hOP, x + 0, y + 0, str, color);
	Draw(hOP, x + 0, y + 1, (char*)"■", color);
	Draw(hOP, x + 2, y + 0, (char*)"■", color);
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
			if (i == 4 && j == 4) {
				isComplete = true;
			}
				
				

			if (puzzle[i][j] !=  j + 1 + i * 5)
				break;
		}
	}

	return isComplete;
}