// ConsoleApplication10.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include <time.h>

// 열거문 enum
// enum 은 여러가지 상태 값을 문자로 표현할 수 있다. (가독성이 증가)
// 값을 순차적으로 증가시키며 관리한다. (값을 임의로 정해주면 그 값부터 뒤에서 1씩 증가한다.)
using namespace std;

//캐릭터의 상태값
enum E_STATE { E_IDLE = 0, E_MOVE_LEFT, E_MOVE_RIGHT, E_MOVE_UP, E_MOVE_DOWN, E_FIGHT, E_STATE_MAX};
//전투 중 캐릭터의 상태값
enum E_FIGHTING { E_RUNAWAY, E_ATTACK,  E_MAGIC, E_HEAL};
//몬스터 종류
enum E_MONTYPE { E_ORC, E_DARKELF, E_TROLL,E_HUMAN, E_MON_MAX};

int mobattack() {
	int nCrirand = rand() % 3;
	if (nCrirand == 0) {
		cout << "몬스터의 공격! 크리티컬! 20데미지!" << endl;
		return 20;
	}
	else {
		cout << "몬스터의 공격! 10데미지!" << endl;
		return  10;
	}
}
bool isAlive(int nHp) {
	if (nHp > 0) {
		cout << "남은 체력 : " << nHp << endl;
		return true;
	}
	else {
		cout << "플레이어가 사망! 게임 종료!" << endl;
		return false;
	}
}


int main()
{
	srand(time(NULL));
	rand();

	E_STATE eState = E_IDLE;//캐릭터의 현재 상태
	E_MONTYPE eMonid;
	int nHp = 100;//캐릭터의 체력
	int nCoordX = 0, nCoordY = 0;//캐릭터의 좌표값
	int nSelect; // 행동을 입력받기 위한 변수
	bool isGame= true;

	//최댓값=현재 3이므로 몬스터 종류가 추가되더라도 수정할 필요가 없음
	int nMonHp[E_MON_MAX];
	int nMonDef[E_MON_MAX];
	int nMonX[E_MON_MAX];
	int nMonY[E_MON_MAX];

	for (int i = 0; i < E_MON_MAX; i++) {
		nMonHp[i] = 50+5*i;
		nMonDef[i] = E_MON_MAX*5-5 * i;
		nMonX[i] = 5 + i * 5;
		nMonY[i] = 0;
	}

	while (isGame)
	{
		system("cls");


		cout << "현재 위치 : X(" << nCoordX << ") Y(" << nCoordY << ")" << endl;

		if (eState == E_IDLE)
			cout << "입력하시오. (0.대기 1.왼쪽 2.오른쪽 3.위쪽 4.아래쪽) : ";
		else if (eState == E_FIGHT)
			cout << "입력하시오. (0.도망 1.공격 2.마법공격 3.치유) : ";

		cin >> nSelect;

		cout << ".";
		Sleep(300);
		cout << ".";
		Sleep(300);
		cout << ".";
		Sleep(300);

		if (eState == E_IDLE) {
			switch (nSelect)
			{
			case E_IDLE: {
				cout << "한턴 휴식" << endl;
			}
			break;
			case E_MOVE_LEFT: {
				cout << "왼쪽으로 한칸 이동" << endl;
				nCoordX--;
			}
			break;
			case E_MOVE_RIGHT: {
				cout << "오른쪽으로 한칸 이동" << endl;
				nCoordX++;
			}
			break;
			case E_MOVE_UP: {
				cout << "위쪽으로 한칸 이동" << endl;
				nCoordY++;
			}
			break;
			case E_MOVE_DOWN: {
				cout << "아래쪽으로 한칸 이동" << endl;
				nCoordY--;
			}
			break;
			default: {
				cout << "잘못된 입력! 강제로 한 턴 휴식!" << endl;
			}
			break;
			}


			for (int i = 0; i < E_MON_MAX; i++)
			{
				if (nCoordX == nMonX[i] && nCoordY == nMonY[i] && nMonHp[i]!=0) {
					switch (i)
					{
					case E_ORC:
						cout << "오크를 만났다!" << endl;
						eMonid = E_ORC;
						eState = E_FIGHT;
						break;
					case E_DARKELF:
						cout << "다크엘프를 만났다!" << endl;
						eMonid = E_DARKELF;
						eState = E_FIGHT;
						break;
					case E_TROLL:
						cout << "트롤을 만났다!" << endl;
						eMonid = E_TROLL;
						eState = E_FIGHT;
						;
					case E_HUMAN:
						cout << "도적을 만났다!" << endl;
						eMonid = E_HUMAN;
						eState = E_FIGHT;
						;
					default:
						break;
					}

				}
			}
		}

		else if (eState == E_FIGHT) {
			switch (nSelect)
				{
				case E_RUNAWAY:
				{
					int nRand = rand() % 2;
					if (nRand == 0) {
						cout << "도주 성공!!!" << endl;
						nCoordX++;
						eState = E_IDLE;
					}
					else {
						
						cout << "도주 실패!!!" << endl;
						nHp -= mobattack();
						isGame = isAlive(nHp);
					}
				}
				break;
				case E_ATTACK: {//20의 데미지를 입힘.
					nMonHp[eMonid] -= (20 - nMonDef[eMonid]);
					cout << "물리 공격! "<< (20 - nMonDef[eMonid])<<"의 공격을 가했다! 몬스터의 남은 체력:" << nMonHp[eMonid]<< endl;
					if (nMonHp[eMonid] == 0) {
						cout << "몬스터가 쓰러졌다! 체력 모두 회복!" << endl;
						eState = E_IDLE;
						nHp = 100;
					}
					nHp -= mobattack();
					isGame = isAlive(nHp);
				}
				break;
				case E_MAGIC: {//방어무시 10의 데미지를 입힘
					nMonHp[eMonid] -= 10 ;
					cout << "마법 공격! " << 10 << "의 방어 무시 공격을 가했다! 몬스터의 남은 체력:" << nMonHp[eMonid] << endl;
					if (nMonHp[eMonid] == 0) {
						cout << "몬스터가 쓰러졌다! 체력 모두 회복!" << endl;
						eState = E_IDLE;
						nHp = 100;
					}
					nHp -= mobattack();
					isGame = isAlive(nHp);
				}
				break;
				case E_HEAL: {// 15의 데미지 치유
					nHp += 15;
					cout << "치유 마법 전개! 15의 체력을 회복하여 " << nHp << "의 체력이 되었다!" << endl;
					nHp -= mobattack();
					isGame = isAlive(nHp);
				}
				break;
				default:{
					cout << "잘못된 입력! 강제로 한 턴 휴식!" << endl;
				break;
				}
			}
		}
				
		Sleep(1500);
	}



	system("pause");
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
