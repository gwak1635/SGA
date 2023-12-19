﻿// Report5.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    rand();

    int nWhoatt = 0;
    int nPlaWin = 0;
    int nComWin = 0;
    int nCom;
    int nPlayer;
    bool isContinue = true;
    while (isContinue) {
        // 0<1, 1<2, 2<0
        while (true) {

            nCom = rand() % 3;
            cout << "0:가위 1:바위 2:보 : ";
            cin >> nPlayer;

            cout << "컴퓨터: " << nCom << " vs " << nPlayer << " :플레이어" << endl;

            if (nCom == nPlayer) {
                cout << "무승부" << endl;
            }
            else if ((nCom + 1) % 3 == nPlayer) {
                cout << "플레이어 공격권" << endl;
                nWhoatt = 1;
                break;
            }
            else {
                cout << "컴퓨터 공격권" << endl;
                nWhoatt = 2;
                break;
            }

        }

        cout << "===================================" << endl;


        while (true) {
            nCom = rand() % 3;
            cout << "0:가위 1:바위 2:보 : ";
            cin >> nPlayer;

            cout << "컴퓨터: " << nCom << " vs " << nPlayer << " :플레이어" << endl;

            if (nCom == nPlayer) {
                if (nWhoatt == 1) {
                    cout << "플레이어 승리" << endl;
                    nPlaWin++;
                }
                else {
                    cout << "컴퓨터 승리" << endl;
                    nComWin++;
                }
                break;
            }
            else if ((nCom + 1) % 3 == nPlayer) {
                cout << "플레이어 공격권" << endl;
                nWhoatt = 1;
            }
            else {
                cout << "컴퓨터 공격권" << endl;
                nWhoatt = 2;

            }
        }
        cout << "===================================" << endl;
        cout << "플레이어 - " << nPlaWin << " vs " << nComWin << " - 컴퓨터" << endl;
        cout << "===================================" << endl;
        if (nPlaWin == 2) {
            cout << "플레이어 최종 승리!";
            isContinue = false;
        }
        else if (nComWin == 2) {
            cout << "컴퓨터 최종 승리!";
            isContinue = false;
        }
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
