// ConsoleApplication7.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>

using namespace std;
/*
카드: 1~12까지의 숫자 카드
1. 카드 2장이 랜덤하게 선택되고 플레이어에게 보여짐.
1.5 카드 1장은 선택이 되나 경기 종료까지 오픈되지 않음.
ex)7~10
2. 기본 베팅 200
3. 게임 포기 시 100 회수, 스탑 : 승부, 추가 배팅 : 따블-카드 추가 오픈 3
=> 승부 : 숨겨진 카드가 위에 오픈된 두 숫자 사이의 카드라면 승리) 숨겨진 카드 9
=> 추가 배팅 : 선택되지 않은 카드 중에 한 장이 오픈된다.

*/
enum E_SELECT { E_GIVEUP = 0, E_SEUNGBU, E_ADDBET };

int main()
{
	srand(time(NULL));
	rand();

	// 플레이어의 총 금액, 배팅 금액, 카드 12장(배열), 추가배팅 카운트[3], 게임 지속,
	//배열의[0,1] 오픈 [2] 승부 [3,4,5] 추가 배팅시 오픈 카드

	int nMoney = 200;
	int nBet = 0;
	int nExbet = 0;
	int nCards[12] = { 0, };
	bool isGame = true;
	char cContinue = NULL;



	while (isGame) {
		

		for (int i = 0; i < 12; i++)
			nCards[i] = i + 1;

		for (int i = 0; i < 120; i++) {
			int nSrc = rand() % 12;
			int nDest = rand() % 12;

			int nTemp = nCards[nSrc];
			nCards[nSrc] = nCards[nDest];
			nCards[nDest] = nTemp;
		}

		nExbet = 1;
		nBet = 200;

		if (nCards[0] > nCards[1]) {
			int nTemp = nCards[0];
			nCards[0] = nCards[1];
			nCards[1] = nTemp;
		}

		while(true) {
			system("cls");
			cout << "현재 보유 금액 : " << nMoney << endl;
			cout << "===============================" << endl;
			cout << "현재 베팅 금액 : " << nBet * nExbet << endl;
			cout << "오픈 카드 : " << nCards[0] << " ~ " << nCards[1] << endl;
			cout << "승부 카드 : ?" << endl;

			cout << "추가 오픈 : ";

			int nIndex = 0;
			for (int i = 2; i <= nExbet; i *= 2) {
				cout << nCards[3 + (nIndex++)] << "\t";

			}
			for (int i = nExbet; i <8; i *= 2) {
				cout << "\t?";

			}

			cout << endl;

			int nSelect;
			cout << "1.포기, 2.승부, 3.추가베팅 : ";
			cin >> nSelect;
			nSelect--;

			switch (nSelect) {
			case E_GIVEUP:
				cout << "게임 포기!!" << endl;
				cout << "승부 카드 : " << nCards[2] << endl;
				nMoney -= nBet * nExbet / 2;
				break;
			case E_SEUNGBU:
				cout << "승부~!!!" << endl;
				cout << "승부 카드 : " << nCards[2] << endl;

				if (nCards[0] < nCards[2] && nCards[2] < nCards[1]) {
					cout << "플레이어 승리!!" << endl;
					nMoney += nBet * nExbet;

				}
				else {
					cout << "플레이어 패배!!" << endl;
					nMoney -= nBet * nExbet;
					
				}
				break;
			case E_ADDBET:
				if (nMoney < nBet * nExbet * 2) {
					"보유 금액 부족";
				}
				else
					nExbet *= 2;
			
			default:
				cout << "선택 범위 안에서 숫자를 고르시오." << endl;
				break;
			}
		
		}
		cout << "다음 게임 (y/n) : ";
		char chYN;
		cin >> chYN;


		if (nMoney < 200) {
			cout << "더 이상 플레이를 할 금액이 없습니다." << endl
			<< "게임을 종료합니다." << endl;
			isGame = false;
		}
		if ((chYN == 'N' || chYN == 'n')&&nMoney>=200)
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
