// ConsoleApplication5.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	//셔플:랜덤하게 섞되, 같은 값은 나오지 않음


	srand(time(NULL));
	rand();

	int	nCom[9];
	int nIn[3];
	bool isGame = true;
	char cYn;

	while (isGame) {
		
		for (int i = 0; i < 9; i++)
			nCom[i] = i + 1;

		for (int i = 0; i < 100; i++) {
			int nSrc = rand() % 9;
			int nDest = rand() % 9;

			int nTemp = nCom[nSrc];
			nCom[nSrc] = nCom[nDest];
			nCom[nDest] = nTemp;
		}

		cout << "숫자 야구 게임" << endl;
		int nInning = 0;
		while (true) {
			cout << "=====================================" << endl;

			nInning++;
			cout << nInning << " 이닝." << endl;
			cout << "숫자 3개를 입력하시오(예시: 1 2 3) : ";
			cin >> nIn[0] >> nIn[1] >> nIn[2];

			int nSt = 0;
			int nBa = 0;
			int nOut = 0;
			
			for (int i = 0; i < 3; i++) {
				if (nIn[i] == nCom[i])
					nSt++;
				else if (nIn[i] == nCom[(i+1)%3] || nIn[i] == nCom[(i+2)%3])
					nBa++;
				else nOut++;
			}

			cout << "스트라이크 : " << nSt << endl;
			cout << "볼 : " << nBa << endl;
			cout << "아웃 : " << nOut << endl;

			if (nSt == 3) {
				cout << "=====================================" << endl;
				cout << "게임 승리! 숫자: (" << nCom[0] << ", " << nCom[1] << ", " << nCom[2] << "), " << nInning << "이닝" << endl;
				break;
			}

		}
		cout << "게임을 계속하시겠습니까? (y, n) : ";
		cin >> cYn;
		if (cYn == 'Y' || cYn == 'y')
			continue;
		else
			isGame = false;
	}
	
	

	system("pause");
	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
