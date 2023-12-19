// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

//void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

//게임 함수들
void CreateBlock(int puzzle[4][4]);									//퍼즐 초기화 함수
void Keyboard(bool* playing, int puzzle[4][4], bool* moved);		//게임 주요 로직 함수(키보드 입력시 블록 이동, 합체)
int Check(int puzzle[4][4]);										//게임 승/패 결정 함수

void PrintPuzzle(HANDLE hOP, int puzzle[4][4]);						//화면에 퍼즐을 그려주는 함수
void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color, bool isNotoverthreedigit);	//퍼즐을 블럭별로 그려주는 함수;


int main()
{
	system("mode con:lines=22 cols=42");//콘솔창의 가로세로 크기 지정

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
	bool isMoved = false;
	int nNonewinlose = 0;
	int nPuzzle[4][4] = { 0, };

	CreateBlock(nPuzzle);
	CreateBlock(nPuzzle);
	PrintPuzzle(hOP, nPuzzle);

	while (isPlaying) {

		if (_kbhit())//키 버퍼 확인 함수(bool형 반환)
		{
			system("cls");
			
			//블럭이 한번이라도 이동했다면 true가 되는 변수
			isMoved = false;

			Keyboard(&isPlaying, nPuzzle, &isMoved);

			if (isMoved) {
				CreateBlock(nPuzzle);
				nNonewinlose = Check(nPuzzle);
			}
			PrintPuzzle(hOP, nPuzzle);

			switch (nNonewinlose) {
			case 1:
				cout << "게임 승리! 게임을 종료합니다." << endl;
				isPlaying = false;
				break;
			case 2:
				cout << "게임 패배! 게임을 종료합니다." << endl;
				isPlaying = false;
				break;
			}

			while (_kbhit()) _getch();//버퍼 비우기
			//이 함수는 입력된 키보드 값을 변수로 바로 저장할 때도 사용됨
			//nKeyValue = getch(); 
		}
	}

	return 0;
}


void Draw(HANDLE hOP, int x, int y, char* str, WORD color) {
	
	DWORD dwCharsWritten;
	COORD cdFill = { x,y };

	//색상을 칠해주는 함수
	FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	//문자를 적어주는 함수
	WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
}

void CreateBlock(int puzzle[4][4]) {
	
	int nIndex = 0;

	int nEmpty[16] = { 0, };

	for (int i = 0; i < 16; i++)
	{
		if (puzzle[i / 4][i % 4] == 0)
			nEmpty[i] = i;
	}

	for (int i = 0; i < 500; i++)
	{
		int nTemp;
		int nSrc = rand() % 16;
		int nDest = rand() % 16;

		nTemp = nEmpty[nSrc];
		nEmpty[nSrc] = nEmpty[nDest];
		nEmpty[nDest] = nTemp;
	}
	
	for (int i = 0; i < 16; i++)
	{
		if (nEmpty[i] != 0) {
			nIndex = nEmpty[i];
		}
	}

	int nProbability = rand() % 10;

	if (nProbability == 0) {
		puzzle[nIndex / 4][nIndex % 4] = 4;
	}
	else
	{
		puzzle[nIndex / 4][nIndex % 4] = 2;
	}
}

void Keyboard(bool* playing, int puzzle[4][4], bool* moved) {


	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽 방향키
	{
		for (int i = 0; i < 4; i++)
		{
			//'오른쪽 끝'에 대한 정의
			for (int j = 3; j >= 1; j--)
			{
				//만약 오른쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[i][j] == 0)
				{
					//'오른쪽 끝'의 바로 왼쪽 블록부터 '왼쪽으로' 탐색
					for (int k = j - 1; k >= 0; k--)
					{
						if (puzzle[i][k] != 0) {
							puzzle[i][j] = puzzle[i][k];
							puzzle[i][k] = 0;
							*moved = true;
							break;
						}
					}
				}
			}
			for (int j = 3; j >= 1; j--)
			{
				//만약 오른쪽 끝 블록이 0이 아니고 바로 왼쪽 블록과 같다면 (블록 결합)
				if (puzzle[i][j] == puzzle[i][j - 1] && puzzle[i][j] != 0)
				{
					puzzle[i][j] *= 2;
					puzzle[i][j - 1] = 0;
					*moved = true;
				}
			}
			//'오른쪽 끝'에 대한 정의
			for (int j = 3; j >= 1; j--)
			{
				//만약 오른쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[i][j] == 0)
				{
					//'오른쪽 끝'의 바로 왼쪽 블록부터 '왼쪽으로' 탐색
					for (int k = j - 1; k >= 0; k--)
					{
						if (puzzle[i][k] != 0) {
							puzzle[i][j] = puzzle[i][k];
							puzzle[i][k] = 0;
							*moved = true;
							break;
						}
					}
				}
			}
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽 방향키
	{
		for (int i = 0; i < 4; i++)
		{
			//'왼쪽 끝'에 대한 정의
			for (int j = 0; j <= 3; j++)
			{
				//만약 왼쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[i][j] == 0)
				{
					//'왼쪽 끝'의 바로 오른쪽 블록부터 '오른쪽으로' 탐색
					for (int k = j + 1; k <= 3; k++)
					{
						if (puzzle[i][k] != 0) {
							puzzle[i][j] = puzzle[i][k];
							puzzle[i][k] = 0;
							*moved = true;
							break;
						}
					}
				}

			}
			for (int j = 0; j <= 3; j++)
			{
				//만약 왼쪽 끝 블록이 0이 아니고 바로 오른쪽 블록과 같다면 (블록 결합)
				if (puzzle[i][j] == puzzle[i][j + 1] && puzzle[i][j] != 0)
				{
					puzzle[i][j] *= 2;
					puzzle[i][j + 1] = 0;
					*moved = true;
				}
			}
			//'왼쪽 끝'에 대한 정의
			for (int j = 0; j <= 3; j++)
			{
				//만약 왼쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[i][j] == 0)
				{
					//'왼쪽 끝'의 바로 오른쪽 블록부터 '오른쪽으로' 탐색
					for (int k = j + 1; k <= 3; k++)
					{
						if (puzzle[i][k] != 0) {
							puzzle[i][j] = puzzle[i][k];
							puzzle[i][k] = 0;
							*moved = true;
							break;
						}
					}
				}

			}
		}

	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) //위쪽 방향키
	{
		for (int i = 0; i < 4; i++)
		{
			//'위쪽 끝'에 대한 정의
			for (int j = 0; j <= 3; j++)
			{
				//만약 위쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[j][i] == 0)
				{
					//'위쪽 끝'의 바로 아래쪽 블록부터 '아래쪽으로' 탐색
					for (int k = j + 1; k <= 3; k++)
					{
						if (puzzle[k][i] != 0) {
							puzzle[j][i] = puzzle[k][i];
							puzzle[k][i] = 0;
							*moved = true;
							break;
						}
					}
				}

			}
			for (int j = 0; j <= 3; j++)
			{
				//만약 위쪽 끝 블록이 0이 아니고 바로 아래쪽 블록과 같다면 (블록 결합)
				if (puzzle[j][i] == puzzle[j + 1][i] && puzzle[j][i] != 0)
				{
					puzzle[j][i] *= 2;
					puzzle[j + 1][i] = 0;
					*moved = true;
				}
			}
			//'위쪽 끝'에 대한 정의
			for (int j = 0; j <= 3; j++)
			{
				//만약 위쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[j][i] == 0)
				{
					//'위쪽 끝'의 바로 아래쪽 블록부터 '아래쪽으로' 탐색
					for (int k = j + 1; k <= 3; k++)
					{
						if (puzzle[k][i] != 0) {
							puzzle[j][i] = puzzle[k][i];
							puzzle[k][i] = 0;
							*moved = true;
							break;
						}
					}
				}

			}
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) //아래쪽 방향키
	{
		for (int i = 0; i < 4; i++)
		{
			//'아래쪽 끝'에 대한 정의
			for (int j = 3; j >= 1; j--)
			{
				//만약 아래쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[j][i] == 0)
				{
					//'아래쪽 끝'의 바로 위쪽 블록부터 '위쪽으로' 탐색
					for (int k = j - 1; k >= 0; k--)
					{
						if (puzzle[k][i] != 0) {
							puzzle[j][i] = puzzle[k][i];
							puzzle[k][i] = 0;
							*moved = true;
							break;
						}
					}
				}

			}
			for (int j = 3; j >= 1; j--)
			{
				//만약 아래쪽 끝 블록이 0이 아니고 바로 위쪽 블록과 같다면 (블록 결합)
				if (puzzle[j][i] == puzzle[j - 1][i] && puzzle[j][i] != 0)
				{
					puzzle[j][i] *= 2;
					puzzle[j - 1][i] = 0;
					*moved = true;
				}
			}
			//'아래쪽 끝'에 대한 정의
			for (int j = 3; j >= 1; j--)
			{
				//만약 아래쪽 끝 블록이 0이라면 (블록 이동)
				if (puzzle[j][i] == 0)
				{
					//'아래쪽 끝'의 바로 위쪽 블록부터 '위쪽으로' 탐색
					for (int k = j - 1; k >= 0; k--)
					{
						if (puzzle[k][i] != 0) {
							puzzle[j][i] = puzzle[k][i];
							puzzle[k][i] = 0;
							*moved = true;
							break;
						}
					}
				}

			}
		}
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) //아래쪽 방향키
		*playing = false;

}

int Check(int puzzle[4][4]) {


	//승리 조건
	for (int i = 0; i < 16; i++)
	{
		if (puzzle[i / 4][i % 4] >= 2048) {
			return 1;
		}
	}

	//패배 조건
	//모든 칸이 꽉 차면 true로 변경해 줌
	bool isFull = false;
	for (int i = 0; i < 16; i++)
	{
		if (puzzle[i/4][i%4] == 0) {
			break;
		}
		if (i == 15) {
			isFull = true;
		}
	}

	if (isFull) {
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++)
			{
				if (puzzle[i][j] == puzzle[i][j + 1]) {
					return 0;
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++)
			{
				if (puzzle[i][j] == puzzle[i+1][j]) {
					return 0;
				}
			}
		}
		return 2;
	}


	//아무 일 없을 때
	return 0;
}

void PrintPuzzle(HANDLE hOP, int puzzle[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			char* szTemp = new char;

			if (puzzle[i][j]==0) {
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, (char*)"■", BG_WHITE|FG_BLACK,true);
			}
			else if (puzzle[i][j]<100){
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j], szTemp, 10), BG_YELLOW | FG_BLACK,true);
			}
			else {
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j], szTemp, 10), BG_YELLOW | FG_BLACK,false);
			}
				
		}
	}
}

void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color, bool isNotoverthreedigit) {
	Draw(hOP, x + 0, y + 0, str, color);
	if (isNotoverthreedigit)
		Draw(hOP, x + 2, y + 0, (char*)"■", color);
	Draw(hOP, x + 0, y + 1, (char*)"■", color);
	Draw(hOP, x + 2, y + 1, (char*)"■", color);
}

