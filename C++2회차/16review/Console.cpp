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
    
    //테이블 생성
    int nUserTable[25];
    int nUserBingo = 0;
    
    int nComTable[25];
    int nComBingo = 0;

    // 게임 진행 변수 선언
    bool isPlaying = true;
    bool isMyTurn = true;

    InitTable(nUserTable);
    InitTable(nComTable);

    while (isPlaying) {
        //게임 진행
        while (true) {
            system("cls");
            //빙고 확인. 대충 체크빙고 리턴값
            nUserBingo=CheckBingo(nUserTable);
            nComBingo=CheckBingo(nComTable);

            //테이블 확인
            ShowTable(nComTable);
            cout <<"컴퓨터 빙고 : "<< nComBingo << endl << endl;
            ShowTable(nUserTable);
            cout << "유저 빙고 : " << nUserBingo << endl << endl;

            //조건 만족 시 게임 종료
            if (nUserBingo >= 3 && nComBingo >= 3) {
                cout << "3빙고 동시 달성! 무승부!" << endl;
                break;
            }
            else if (nUserBingo >= 3) {
                cout << "플레이어 3빙고 동시 달성! 승리!" << endl;
                break;
            }
            else if (nComBingo >= 3) {
                cout << "유저 3빙고 동시 달성! 패배!" << endl;
                break;
            }

            //숫자 입력
            if (isMyTurn) {
                UserSelect(nUserTable, nComTable);
                isMyTurn = false;
            }
            else {
                ComSelect(nUserTable, nComTable);
                isMyTurn = true;
            }
        }
        cout << "0. 게임 종료 1. 새 게임 : " << endl;
        cin >> isPlaying;
        
    }
       

    return 0;
}
    
void InitTable(int* table) {
    for (int i = 0; i < 25; i++)
    {
        table[i] = i + 1;
    }

    int nSrc;
    int nDest;
    int nTemp;

    for (int i = 0; i < 625; i++)
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
    for (int i = 0; i < 25; i++)
    {
        cout << "|  " << table[i] << "\t|";
        if (i % 5 == 4) {
            cout << endl;
            cout << "=========================================" << endl;
        }
            

    }
}
void HideTable(int* table) {
    cout << "=========================================" << endl;
    for (int i = 0; i < 25; i++)
    {
        if (table[i] == 0) {
            cout << "|  " << 0 << "\t|";
        }
        else {
            cout << "|  " << "?" << "\t|";
        }
        if (i % 5 == 4) {
            cout << endl;
            cout << "=========================================" << endl;
        }


    }
}
void UserSelect(int* userTable, int* comTable) {
    int nSelect = 0;
    
    cout << "숫자 입력 : ";
    cin >> nSelect;

    for (int i = 0; i < 25; i++)
    {
        if (userTable[i] == nSelect) {
            userTable[i] = 0;
            for (int j = 0; j < 25; j++)
            {
                if (comTable[j] == nSelect) {
                    comTable[j] = 0;
                    break;
                }                
            }
            break;
        }

        if (i == 24) {
            cout << "올바른 값을 입력해 주십시오." << endl;
            Sleep(2000);
        }

    }
}
void ComSelect(int* userTable, int* comTable) {
    int nIndex;
    int nSelect = 0;
    
    cout << "컴퓨터가 선택 중";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << "."<<endl;

    //nSelect가 0이 아닐때까지 무한반복
    while (nSelect == 0) {
        nIndex = rand() % 25;
        nSelect = comTable[nIndex];
    }

    for (int i = 0; i < 25; i++)
    {
        if (userTable[i] == nSelect) {
            userTable[i] = 0;
        }
        if (comTable[i] == nSelect) {
            comTable[i] = 0;
        }
    }


    cout << "컴퓨터가 선택한 값 : " << nSelect << endl;
    Sleep(2000);
}
int CheckBingo(int* table) {
    int nBingo = 0;

    //가로줄 빙고

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i * 5 + j] == 0) {
                if (j == 4) {
                    nBingo++;
                }
            }
            else {
                break;
            }
        }
    }
    
    //세로줄 검사
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i  + j * 5] == 0) {
                if (j == 4) {
                    nBingo++;
                }
            }
            else {
                break;
            }
        }
    }

    //↘방향 검사
    for (int i = 0; i < 5; i++)
    {
        if (table[i * 5 + i] == 0) {
            if (i == 4) {
                nBingo++;
            }
        }
        else {
            break;
        }
    }
 
    //↙방향 검사
    for (int i = 0; i < 5; i++)
    {
        if (table[i * 4] == 0) {
            if (i == 4) {
                nBingo++;
            }
        }
        else {
            break;
        }
    }

    return nBingo;

}