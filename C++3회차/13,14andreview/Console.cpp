#include "stdafx.h"

// 열거문 enum
// enum은 여러가지 상태 값을 문자로 표현할 수 있다. (가독성이 증가)
// 값을 순차적으로 증가시키며 관리한다.(값을 임의로 넣는 경우 임의로 정해준 값부터 1씩 증가)
// enum문으로 선언된 변수에 설정된 값에 대한 제한을 걸 수 있다.(실수 방지)
enum E_NUMBERS {EN_ZERO, EN_ONE, EN_TWO, EN_THREE, EN_TEN=10,EN_ELEVEN, EN_MAX};

//캐릭터의 상태값
//ENUM문은 대문자로 사용한다!
enum E_STATE { E_IDLE =0, E_MOVE_LEFT, E_MOVE_RIGHT, E_MOVE_UP, E_MOVE_DOWN,E_FIGHT};
// 전투 중 캐릭터의 상태값
enum E_FIGHTING { E_FLEE, E_ATTACK, E_MAGIC, E_DEFENCE};
// 몬스터 종류
enum E_MONTYPE { E_ORC, E_DARKELF, E_TROLL,E_THIEF, E_MON_MAX};

int main()
{
    srand(time(NULL));
    rand();

    //얘 클래스인데 클래스를 몰?루
    E_STATE eState = E_IDLE; //캐릭터의 현재 상태
    int nHp = 100; //캐릭터의 체력
    int nAtt = 20;
    int nMag = 15;
    int nDef = 10;
    int nCoordX = 0, nCoordY = 0; //캐릭터의 좌푯값
    int nSelect;  //행동을 입력받기 위한 변수
    int nMonrace; //몬스터의 종류

    //몬스터의 수만큼 배열 할당
    int nMonHP[E_MON_MAX]; 
    int nMonX[E_MON_MAX];
    int nMonY[E_MON_MAX];
    int nMonAtt[E_MON_MAX];
    int nMonDef[E_MON_MAX];

    for (int i = 0; i < E_MON_MAX; i++)
    {
        nMonHP[i] = 100;
        nMonX[i] = 5 + i * 5;
        nMonY[i] = 0;
        nMonAtt[i] = 7 + i * 4;
        nMonDef[i] = i * 3;
    }

    bool isAlive = true;

    while (isAlive) {
        system("cls");

        cout << "현재 위치 : X(" << nCoordX << ") Y(" << nCoordY << ")" << endl;

        if (eState == E_IDLE) {
            cout << "입력하시오. (0.대기 1.왼쪽 2.오른쪽 3.위쪽 4.아래쪽) : ";
        }
        else if (eState == E_FIGHT) {
            cout << "입력하시오. (0.도망 1.공격 2.마법공격 3.방어) : ";
        }

        cin >> nSelect;

        cout << ".";
        Sleep(300);
        cout << ".";
        Sleep(300);
        cout << "." << endl;
        Sleep(300);

        if (eState == E_IDLE) {
            switch (nSelect)
            {
            case E_IDLE:
                cout << "한 턴 휴식" << endl;
                break;
            case E_MOVE_LEFT:
                cout << "왼쪽으로 한 칸 이동" << endl;
                nCoordX--;
                break;
            case E_MOVE_RIGHT:
                cout << "오른쪽으로 한 칸 이동" << endl;
                nCoordX++;
                break;
            case E_MOVE_UP:
                cout << "위쪽으로 한 칸 이동" << endl;
                nCoordY++;
                break;
            case E_MOVE_DOWN:
                cout << "아래쪽으로 한 칸 이동" << endl;
                nCoordY--;
                break;
            default:
                cout << "잘못된 입력! 강제로 한 턴 휴식!" << endl;
                break;
            }

            for (int i = 0; i < E_MON_MAX; i++)
            {
                if (nCoordX == nMonX[i] && nCoordY == nMonY[i] && nMonHP[i]>0) {
                    switch (i)
                    {
                    case E_ORC:
                        cout << "오크를 만났다!" << endl;
                        nMonrace = i;
                        break;
                    case E_DARKELF:
                        cout << "다크엘프를 만났다!" << endl;
                        nMonrace = i;
                        break;
                    case E_TROLL:
                        cout << "트롤을 만났다!" << endl;
                        nMonrace = i;
                        break;
                    case E_THIEF:
                        cout << "도적을 만났다!" << endl;
                        nMonrace = i;
                        break;
                    }

                    eState = E_FIGHT;
                }
            }
        }
        else if (eState == E_FIGHT) {
            switch (nSelect)
            {
            case E_FLEE: {
                if (rand() % 2 == 0) {
                    cout << "도주 성공! 오른쪽으로 한 칸 이동!" << endl;
                    nCoordX++;
                    eState = E_IDLE;
                }
                else {
                    cout << "도주 실패!" << endl;
                }
            }
                       break;
            case E_ATTACK:
            {
                cout << "물리 공격! " << endl;
                int nDamage = nAtt - nMonDef[nMonrace];
                cout << nDamage << "의 데미지를 입혔다!" << endl;
                nMonHP[nMonrace] -= nDamage;
            }
            break;
            case E_MAGIC: {
                cout << "마법 공격! " << endl;
                cout << nMag << "의 데미지를 입혔다!" << endl;
                nMonHP[nMonrace] -= nMag;
            }
                        break;
            case E_DEFENCE: {
                cout << "방어 자세! " << endl;
                cout << nDef << "의 데미지를 이번 턴에 감소한다!" << endl;
            }
                          break;
            default: {
                cout << "잘못된 입력! 강제로 한 턴 휴식!" << endl;
            }
                   break;
            }
            Sleep(1500);
            if (nMonHP[nMonrace] <= 0) {
                cout << "몬스터를 물리쳤다!" << endl;
                eState = E_IDLE;
            }
            else {
                cout << "몬스터의 공격! " << endl;
                {
                    int nDamage = nMonAtt[nMonrace];
                    if (nSelect == E_DEFENCE) {
                        nDamage -= nDef;
                        if (nDamage <= 0)
                            nDamage = 0;
                    }
                    cout << nDamage << "의 데미지를 입었다!" << endl;
                    nHp -= nDamage;

                    if (nHp <= 0) {
                        cout << "죽고 말았다..." << endl;
                        isAlive = false;
                    }
                }
            }
           

        }
        Sleep(1500);

        

    }

    system("pause");

    return 0;
}
