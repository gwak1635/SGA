// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

/*
카드 : 1~12까지의 숫자 카드
1. 컴퓨터가 랜덤하게 선택되고 플레이어에게 보여진다.
1.5 카드 1장은 선택이 되고 경기 종료까지 오픈되지 않는다.
ex) 7 ~ 10
2. 기본 베팅 금액 200
3. 게임 포기 : 100회수, 스탑 : 승부, 추가 베팅 : 카드 추가 오픈(따블)
4. 승부 : 숨겨진 카드가 위 오픈된 두 숫자 사이의 카드라면 승리
5. 추각 베팅 : 선택되지 않은 카드 중에 한장이 오픈된다.
*추가 베팅된 카드는 승부 범위에 영향을 끼치지 않는다!
*/

int main()
{
    srand(time(NULL));
    rand();

    bool isPlaying = true;
    int nMoney = 4000;
    int nCard[12];
    int nBet;
    int nExbet;
    for (int i = 0; i <= 11; i++)
    {
        nCard[i] = i + 1;
    }

    while (isPlaying) {

        system("cls");

        for (int i = 0; i < 150; i++)
        {
            int nSrc = rand() % 12;
            int nDest = rand() % 12;
            int nTemp;

            nTemp = nCard[nSrc];
            nCard[nSrc] = nCard[nDest];
            nCard[nDest] = nTemp;
        }

        nBet = 200;
        nExbet = 1;// 1 2 4 8

        if (nCard[0] > nCard[1]) {
            int nTemp = nCard[0];
            nCard[0] = nCard[1];
            nCard[1] = nTemp;
        }
        while (true)
        {
            cout << "현재 금액 : " << nMoney << endl;
            cout << "============================" << endl;
            cout << "베팅 금액 : " << nBet * nExbet << endl;

            cout << "오픈 카드 : " << nCard[0] << " ~ " << nCard[1] << endl;
            cout << "승부 카드 : ?" << endl;
            cout << "추가 오픈 : ";

            int nIndex = 0;
            for (int i = 1; i < nExbet; i *= 2) {
                cout << nCard[3 + (nIndex++)] << "\t";
            }//1

            for (int i = nExbet; i < 8; i *=2 )
            {
                cout << "?\t";
            }//2 4
            cout << endl;
            

            int nSelect;
            bool isExbetable;
            if (nMoney>= nBet * nExbet*2 && nExbet < 8) {
                isExbetable = true;
            }
            else {
                isExbetable = false;
            }

            if (isExbetable) {
                cout << "1.포기(반액 환수), 2.승부, 3.추가 오픈(베팅 금액 2배), 0.게임 종료" << endl;
            }
            else {
                cout << "1.포기(반액 환수), 2.승부, 0.게임 종료" << endl;
            }
            cout << "선택하시오 : ";
            cin >> nSelect;

            if (nSelect == 1) {
                cout << "게임 포기. 반액이 환수됩니다." << endl;
                cout << "승부 카드 : " << nCard[2] << endl;
                nMoney -= nBet * nExbet / 2;
                break;
            }
            else if (nSelect == 2) {
                cout << "승부!" << endl;
                cout << "승부 카드 : " << nCard[2] << endl;
                if (nCard[0] < nCard[2] && nCard[2] < nCard[1]) {
                    cout << "승리!" << endl;
                    nMoney += nBet * nExbet;
                }
                else {
                    cout << "패배!" << endl;
                    nMoney -= nBet * nExbet;
                }
                break;
            }
            else if (nSelect == 3&& isExbetable) {
                nExbet *= 2;
            }
            else if (nSelect == 0) {
                cout << "게임을 종료합니다." << endl;
                isPlaying = false;
                break;
            }
            else {
                cout << "유효한 값이 아닙니다." << endl;
                system("pause");
            }
            
        }

        system("pause");


        if (nMoney < 200) {
            cout << "더 이상 베팅할 금액이 없습니다. 게임을 종료합니다." << endl;
            isPlaying = false;
        }


    }

    system("pause");

    return 0;
}