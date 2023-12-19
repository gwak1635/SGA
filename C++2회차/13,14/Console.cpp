// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

enum E_NUMBERS { EN_ZERO, EN_ONE, EN_TWO, EN_THREE, EN_TEN=10, EN_ELEVEN};

//여러 가지 상태값을 문자로 표현할 수 있다(가독성 증가)
// 숫자를 문자로 바꾸는 바법?
//ENUM은 앞에 E_를 붙이고, 대문자를 표시함. 순차 배열
enum E_STATE {E_IDLE=0, E_MOVE_LEFT, E_MOVE_RIGHT, E_MOVE_UP, E_MOVE_DOWN, E_FIGHT, E_STATE_MAX};
//전투 중 캐릭터의 상태값
enum E_FIGHTING {E_RUNAWAY, E_ATTACK, E_MAGIC, E_DEFENCE, E_F_MAX};
//몬스터 종류
enum E_MONTYPE {E_ORC, E_DARKELF, E_TROLL,E_THIEF, E_MON_MAX};

int main()
{
    srand(time(NULL));
    rand();

    //처음부터 enum문으로 선언하면 변수 제한이 가능하다
    //switch로 자동완성이 됨.
    E_STATE eState = E_IDLE;
    E_MONTYPE eMontype;
    int nHp = 100;
    int nCoordX = 0, nCoordY = 0;
    int nSelect;
    bool isDefence= false;
    bool isPlaying = true;

    //몬스터의 수 만큼 배열 할당
    int nMonHP[E_MON_MAX];//_MAX의 설정이유(배열의 길이 변경시 수정 용이)
    int nMonX[E_MON_MAX];
    int nMonY[E_MON_MAX];

    for (int i = 0; i < E_MON_MAX; i++)
    {
        nMonHP[i] = 100;
        nMonX[i] = (i + 1) * 5;
        nMonY[i] = 0;
    }

    while (isPlaying) {
        system("cls");

        cout << "현재 위치 X(" << nCoordX << ") Y(" << nCoordY << ")" << endl;

        if (eState == E_IDLE) {
            cout << "입력하시오. (0.대기 1.왼쪽 2. 오른쪽 3.위쪽 4.아래쪽) : ";
        }
        else if (eState == E_FIGHT) {
            cout << "입력하시오. (0.도망 1.공격 2.마법공격 3.방어) : ";
        }
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
                cout << "잘못된 입력입니다. 한 턴 휴식합니다." << endl;
                break;
            }
            for (int i = 0; i < E_MON_MAX; i++)
            {
                if (nCoordX == nMonX[i] && nCoordY == nMonY[i] && nMonHP[i] > 0) {
                    switch (i)
                    {
                    case E_ORC:
                        cout << "오크를 만났다!!" << endl;
                        eMontype = E_ORC;
                        break;
                    case E_DARKELF:
                        cout << "다크엘프를 만났다!!" << endl;
                        eMontype = E_DARKELF;
                        break;
                    case E_TROLL:
                        cout << "트롤을 만났다!!" << endl;
                        eMontype = E_TROLL;
                        break;
                    case E_THIEF:
                        cout << "도적을 만났다!!" << endl;
                        eMontype = E_THIEF;
                        break;
                    }
                    eState = E_FIGHT;
                }
            }
        }
        else if (eState == E_FIGHT) {

            switch (nSelect)
            {
                case E_RUNAWAY:
                {
                    int nRunrand = rand() % 2;
                    if (nRunrand == 0) {
                        cout << "도주 성공! 오른쪽으로 한 칸 이동!" << endl;
                        nCoordX++;
                        eState = E_IDLE;
                    }
                    else {
                        cout << "도주 실패!" << endl;
                    }
                }//굳이 중괄호 쓰는 이유:중괄호 내부에서만 지역 변수가 작동하도록
                break;
                case E_ATTACK:
                    cout << "일반 공격! 몬스터에게 10의 데미지!" << endl;
                    nMonHP[eMontype] -= 10;
                    if (nMonHP[eMontype] <= 0) {
                        cout << "몬스터를 잡았다! 체력 완전 회복!" << endl;
                        eState = E_IDLE;
                        nHp = 100;
                    }                        
                    break;
                case E_MAGIC:
                    cout << "마법 공격! 몬스터에게 15의 데미지!" << endl;
                    nMonHP[eMontype] -= 15;
                    if (nMonHP[eMontype] <= 0) {
                        cout << "몬스터를 잡았다! 체력 완전 회복!" << endl;
                        eState = E_IDLE;
                        nHp = 100;
                    }
                    break;
                case E_DEFENCE:
                    cout << "방어! 다음 턴에 받는 데미지 반감!" << endl;
                    isDefence = true;
                    break;
                default:
                    cout << "잘못된 입력입니다. 한 턴 휴식합니다." << endl;
                    break;
            }
            Sleep(1500);
            if (nMonHP[eMontype] > 0)
            {
                cout << "몬스터의 공격!" << endl;
                if (isDefence) {
                    cout << "방어를 하여 3의 데미지를 입었다!" << endl;
                    nHp -= 3;
                    isDefence = false;
                }
                else {
                    cout << "6의 데미지를 입었다!" << endl;
                    nHp -= 6;
                }
                if (nHp <= 0) {
                    cout << "죽고 말았다... 게임 오버." << endl;
                    isPlaying = false;
                }
            }
        }

       
        Sleep(1500);        
    }

    system("pause");

    return 0;
}
