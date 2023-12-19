// ConsoleApplication6.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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
int main()
{
	srand(time(NULL));
	rand();

	// 플레이어의 총 금액, 배팅 금액, 카드 12장(배열), 추가배팅 카운트[3], 게임 지속,
	//배열의[0,1] 오픈 [2] 승부 [3,4,5] 추가 배팅시 오픈 카드

	int nMoney = 2000;
	int nBetMoney = 0;
	int nExbetcount = 0;
	int aCard[12] = { 0, };
	bool isGame = true;
	char cContinue=NULL;



	while (isGame) {
		system("cls");

		for (int i = 0; i < 12; i++)
			aCard[i] = i + 1;

		for (int i = 0; i < 120; i++) {
			int nSrc = rand() % 12;
			int nDest = rand() % 12;

			int nTemp = aCard[nSrc];
			aCard[nSrc] = aCard[nDest];
			aCard[nDest] = nTemp;
		}
		
		nExbetcount = 0;
		nBetMoney = 200;
		nMoney -= nBetMoney;
		int nSelect = 0;
		bool isSelecting = true;
		int nCardtemp , nCardmin, nCardmax;

		if (aCard[0] < aCard[1]) {
			nCardmin = aCard[0];
			nCardmax = aCard[1];
		}
		else {
			nCardmin = aCard[1]; 
			nCardmax = aCard[0];
		}

		cout << "월남뽕 게임" << endl;
		while (isSelecting) {
			cout << endl;
			cout << "공개된 카드 : " << nCardmin << ", " << nCardmax << endl;
			cout << "현재 금액 : " << nMoney << ", 배팅 금액: " << nBetMoney << ", 현재 추가 배팅 수(최대 3) : " << nExbetcount << endl;
			cout << "1. 게임 포기, 2. 스탑, 3. 추가 배팅 : ";
			cin >> nSelect;
			if (nSelect == 1) {
				cout << "게임을 포기하였습니다. " << nBetMoney << "의 반절만 가져갑니다." << endl;
				nMoney += nBetMoney / 2;
				cout << "잔액: " << nMoney << endl;
				isSelecting = false;
			}
			else if (nSelect == 2) {
				cout << "승부를 보겠습니다. 공개된 숫자는 " << aCard[2] << "입니다." << endl;
				if (nCardmin < aCard[2] && aCard[2] < nCardmax) {
					nMoney += nBetMoney * 2;
					cout << "축하합니다! " << nBetMoney * 2 << "만큼을 획득하여 " << nMoney << "이 되었습니다!" << endl;

				}
				else {
					nBetMoney = 0;
					cout << "이런... 게임에서 졌습니다."<< endl;
				}

				isSelecting = false;
			}
			else {
				if (nExbetcount == 0 && nMoney >= 200) {
					nBetMoney += 200;
					nMoney -= 200;
					
					if (nCardmin < aCard[3] && aCard[3] < nCardmax)
						nCardmin = aCard[3];
					cout << "추가 베팅을 하였습니다. 공개된 숫자는 " << aCard[3] << "입니다." << endl;
					nExbetcount++;
					
				}
				else if (nExbetcount == 1 && nMoney >= 400) {
					nBetMoney += 400;
					nMoney -= 400;

					if (nCardmin < aCard[4] && aCard[4] < nCardmax)
						nCardmin = aCard[4];
					cout << "추가 베팅을 하였습니다. 공개된 숫자는 " << aCard[4] << "입니다." << endl;
					nExbetcount++;
				}
				else if (nExbetcount == 2 && nMoney >= 800) {
					nBetMoney += 800;
					nMoney -= 800;

					if (nCardmin < aCard[5] && aCard[5]< nCardmax)
						nCardmin = aCard[5];
					cout << "추가 베팅을 하였습니다. 공개된 숫자는 " << aCard[5] << "입니다." << endl;
					nExbetcount++;
				}
				else
					cout << "보유하고 있는 돈이 적거나, 추가 베팅 수를 모두 소모하였습니다." << endl;
				

			}
		}

		if (nMoney < 200) {
			cout << "걸 수 있는 돈이 없습니다. 게임을 종료합니다." << endl;
			isGame = false;
			break;
		}
		cout << "계속하시겠습니까? (y,n) : ";
		cin >> cContinue;
		if (cContinue == 'Y' || cContinue == 'y')
			isGame = true;
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
