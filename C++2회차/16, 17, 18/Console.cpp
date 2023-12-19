// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

void InitTable(int* table);
void ShowTable(int* table);
void HideTable(int* table);
void UserSelect(int* userTable, int* comTable);
void ComSelect(int* userTable, int* comTable);
int CheckBingo(int* table);

int main()
{
    srand(time(NULL));
    rand();

    // 테이블 배열과 빙고 변수 선언
    int nUserTable[25];
    int nUserBingo = 0;

    int nComTable[25];
    int nComBingo = 0;

    // 게임 진행 변수 선언
    bool isPlaying = true;
    bool isMyTurn = true;
    //게임 진행
    while (isPlaying) {
        //플레이
        InitTable(nUserTable);
        InitTable(nComTable);

        while (true) {
            system("cls");

             
            //빙고 확인
            nUserBingo = CheckBingo(nUserTable);
            nComBingo = CheckBingo(nComTable);
            
            //테이블 확인
            HideTable(nComTable);
            cout << "컴퓨터 빙고 : " << nComBingo << endl << endl;
            ShowTable(nUserTable);
            cout << "유저 빙고 : " << nUserBingo << endl<<endl;

            if (nUserBingo >= 3 && nComBingo >= 3) {
                cout << "빙고 동시 달성! 무승부!" << endl;
                break;
            }
            else if (nUserBingo >= 3) {
                cout << "유저 빙고 달성! 승리!" << endl;
                break;
            }
            else if (nComBingo >= 3) {
                cout << "컴퓨터 빙고 달성! 패배!" << endl;
                break;
            }
               
            //번호 선택
            if (isMyTurn) {
                UserSelect(nUserTable, nComTable);
                isMyTurn = false;
            }
            else {
                ComSelect(nUserTable, nComTable);
                isMyTurn = true;
            }
        
        }
        

        //플레이 종료
        cout << "0.게임 종료, 1. 새 게임";
        cin >> isPlaying;
    }
}

void InitTable(int* table) {
    for (int i = 0; i < 25; i++)
    {
        table[i] = i + 1;
    }

    int nSrc;
    int nDest;
    int nTemp;

    for (int i = 0; i < 255; i++)
    {
        nSrc = rand() % 25;
        nDest = rand() % 25;

        nTemp = table[nSrc];
        table[nSrc] = table[nDest];
        table[nDest] = nTemp;
    }
}
void ShowTable(int* table) {
    cout << "=========================================" << endl;
    for (int i = 0; i < 25; i++) {
        cout << "|  " << table[i] << "\t|";

        if (i % 5 == 4)
        {
            cout << endl;
            cout << "=========================================" << endl;
        }
    }
}
void HideTable(int* table) {
    cout << "=========================================" << endl;
    for (int i = 0; i < 25; i++) {
        if(table[i] == 0){
            cout << "|  " << 0<< "\t|";
        }
        else {
            cout << "|  " << "?" << "\t|";
        }
        if (i % 5 == 4)
        {
            cout << endl;
            cout << "=========================================" << endl;
        }
    }
}
void UserSelect(int* userTable, int* comTable)
{
    int nSelect;

    cout << "선택 (1~25) : ";
    cin >> nSelect;

    //테이블 전체를 검사
    for (int i = 0; i < 25; i++) {
        if (nSelect == userTable[i]) {
            // 0 = 테이블에서 이미 선택된 숫자를 의미
            userTable[i] = 0;

            for (int j = 0; j < 25; j++) {
                if (nSelect == comTable[j]) {
                    comTable[j] = 0;
                    break;
                }

            }
            break;
        }
        //선택한 숫자를 찾지 못한 경우
        if (i == 24) {
            cout << "올바른 숫자를 선택해 주십시오" << endl;
            Sleep(1000);
        }
    }


}

/* 우선순위 테이블
[3] [0] [0] [0] [4]
[0] [3] [0] [3] [1]
[1] [1] [5] [1  ] [X]
[0] [3] [0] [3] [1]
[3] [0] [0] [0] [4]
*/

void ComSelect(int* userTable, int* comTable)
{
    int nIndex;
    int nSelect;

    cout << "컴퓨터가 선택 중";
   // Sleep(500);
    cout << ".";
   // Sleep(500);
    cout << ".";
   // Sleep(500);
    cout << "." << endl;

    while (true) {
        nIndex = rand() % 25;
        nSelect = comTable[nIndex];
        if (nSelect != 0) {
            //테이블 전체를 검사
            for (int i = 0; i < 25; i++) {
                if (nSelect == userTable[i]) {
                    // 0 = 테이블에서 이미 선택된 숫자를 의미
                    userTable[i] = 0;
                    break;
                }
            }

            comTable[nIndex] = 0;
            break;
        }
    }
   

    cout << "컴퓨터가 선택한 숫자 : " << nSelect<<endl;
  //  Sleep(2000);
}

int CheckBingo(int* table) {
    int nBingo = 0;

    //가로검사 5
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i * 5 + j] == 0) // 한칸씩 선택 유무 확인
            {
                if (j == 4)//제일 마지막까지 선택이 된다면
                    nBingo++;
            }
            else
                break;
        }
    }

    /*
    0  1  2  3  4
    5  6  7  8  9
    10 11 12 13 14
    15 16 17 18 19
    20 21 22 23 24
    */

    //세로 검사 5
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i + j*5] == 0) // 한칸씩 선택 유무 확인
            {
                if (j == 4)//제일 마지막까지 선택이 된다면
                    nBingo++;
            }
            else
                break;
        }
    }
    //왼쪽 위->사선
    for (int i = 0; i < 5; i++)
    {
        if (table[i*5 + i] == 0) // 한칸씩 선택 유무 확인
        {
            if (i == 4)//제일 마지막까지 선택이 된다면
                nBingo++;
        }
        else
            break;
    }

    //오른쪽 위->사선
    for (int i = 0; i < 5; i++)
    {
        if (table[(i+1) * 4] == 0) // 한칸씩 선택 유무 확인
        {
            if (i == 4)//제일 마지막까지 선택이 된다면
                nBingo++;
        }
        else
            break;
    }

    return nBingo;
}
