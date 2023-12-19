// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

void Keyboard(bool* playing, int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

int main()
{
	HANDLE hOP; //핸들 값 가져오기[전체 프로그램 관리]
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);
    
	//커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	bool isPlaying = true;
	int x = 10 , y = 10;

	cout << "x좌표 : " << x << endl;
	cout << "y좌표 : " << y << endl;
	Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);

	while (isPlaying) {
		if (_kbhit())//키 버퍼 확인 함수(bool형 반환)
		{
			Keyboard(&isPlaying, &x, &y);

			system("cls");
			cout << "x좌표 : " << x << endl;
			cout << "y좌표 : " << y << endl;
			Draw(hOP, x*2, y, (char*)"A", BACKGROUND_RED);
			while (_kbhit()) _getch();//버퍼 비우기
			//이 함수는 입력된 키보드 값을 변수로 바로 저장할 때도 사용됨
			//nKeyValue = getch(); 
		}
	}

	return 0;
}

void Keyboard(bool* playing, int* x, int* y) {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽 방향키
		(*x)++;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽 방향키
		(*x)--;
	else if (GetAsyncKeyState(VK_UP) & 0x8000) //위쪽 방향키
		(*y)--;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) //아래쪽 방향키
		(*y)++;
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