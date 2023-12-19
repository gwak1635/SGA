// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

void InitTable(int* table);
void ShowTable(int* table);
void HideTable(int* table);
void UserSelect(int* userTable, int* comTable);
void ComSelect(int* userTable, int* comTable);
void ComSelect2(int* userTable, int* comTable);
int CheckBingo(int* table);

int main()
{
    //랜덤 초기화
    srand(time(NULL));
    rand();

    // 테이블 배열과 빙고 변수 선언
    int nUserTable[25];
    int nUserBingo = 0;
    int nComTable[25];
    int nComBingo = 0;
    

    //게임 진행 변수 선언
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
            cout << endl;
            ShowTable(nUserTable);

            cout << "유저 빙고 : " << nUserBingo << endl << endl;
            cout << "컴퓨터 빙고 : " << nComBingo << endl << endl;


            //게임 종료 판독
            if (nUserBingo >= 3 && nComBingo >= 3) {
                cout << "무승부!" << endl;
                break;
            }
            else if (nUserBingo >= 3) {
                cout << "플레이어 승리!" << endl;
                break;
            }
            else if (nComBingo >= 3) {
                cout << "컴퓨터 승리!" << endl;
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
        
        


        //게임 종료 선택
        cout << "0.게임 종료, 1. 새 게임 : ";
        cin >> isPlaying;
        nUserBingo = 0;
        nComBingo = 0;
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

    for (int i = 0; i < 625; i++) {
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
            cout << "|  0\t|";
        }
        else {
            cout << "|몰?루\t|";
        }
        

        if (i % 5 == 4) {
            cout << endl;
            cout << "=========================================" << endl;
        }
    }
}



void UserSelect(int* userTable, int* comTable) {
    int nSelect;

    cout << "선택 (1 ~ 25) : ";
    cin >> nSelect;

    for (int i = 0; i < 25; i++)
    {
        if (nSelect == userTable[i])
        {
            // 0은 테이블에서 이미 선택된 숫자를 의미함.
            userTable[i] = 0;

            for (int j = 0; j < 25; j++)
            {
                if (nSelect == comTable[j]) {
                    comTable[j] = 0;
                    break;
                }
            }
            break;//전체 for문
        }

        //선택한 숫자를 찾지 못한 경우
        if (i == 24) {
            cout << "올바른 숫자를 입력해 주십시오." << endl;
            Sleep(1000);
        }
    }
}


void ComSelect(int* userTable, int* comTable) {

    int nIndex = 0;
    int nSelect;

    cout << "컴퓨터 선택 중";
    Sleep(333);
    cout << ".";
    Sleep(333);
    cout << ".";
    Sleep(333);
    cout << "." << endl;


    /*
    {4,1,1,1,4},
    {0,3,1,3,0},
    {0,0,5,0,0},
    {0,3,1,3,0},
    {3,0,1,0,3}
    */
    int nPritable[5][5] = {//우선순위 테이블 초기화
    {3,0,0,0,3},
    {0,3,0,3,0},
    {0,0,4,0,0},
    {0,3,0,3,0},
    {3,0,0,0,3}
    };

    for (int i = 0; i < 25; i++)//스캐닝 하기
    {
        if (comTable[i] == 0) {//만약 컴테이블의 값이 0이면
            nPritable[i / 5][i % 5] = -100; //우선순위 테이블의 값을 엄청 낮은 음수로 함과 동시에
            for (int j = 0; j < 5; j++) //우선순위 테이블의 가로,세로,대각선을 1만큼 더한다.
            {
                nPritable[i / 5][j]++;
                nPritable[j][i % 5]++;
                if (i % 6 == 0)
                {
                    nPritable[j][j]++;
                }
                if (i % 4 == 0 && i > 0)
                {
                    nPritable[j][4 - j]++;
                }
            }
        }
    }

    int nMax = -100;//최댓값 선언
    for (int i = 0; i < 25; i++)
    {
        if (nMax < nPritable[i / 5][i % 5]) {
            nMax = nPritable[i / 5][i % 5];//최댓값(우선순위)를 해당 칸의 우선순위만큼 올려줌
        }
    }

    bool nHighstArray[25]{ 0, };

    for (int i = 0; i < 25; i++)//배열에 '최댓값이 들어있는 인덱스 번호'를 넣어줌.
    {
        if (nPritable[i / 5][i % 5] == nMax) {
            nHighstArray[i] = i;
        }
    }

    for (int i = 0; i < 625; i++) //그것을 마구 섞기
    {
        int nTemp;
        int nSrc = rand() % 25;
        int nDest = rand() % 25;

        nTemp = nHighstArray[nSrc];
        nHighstArray[nSrc] = nHighstArray[nDest];
        nHighstArray[nDest] = nTemp;
    }

    for (int i = 0; i < 25; i++)
    {
        if (nHighstArray[i] != 0) {
            nIndex = nHighstArray[i];
        }
    }

    nSelect = comTable[nIndex];

    for (int i = 0; i < 25; i++)//유저 테이블에서 선택된 숫자를 처리하고
    {
        if (nSelect == userTable[i]) {
            userTable[i] = 0;
            break;
        }
    }

    comTable[nIndex] = 0;//컴퓨터 테이블에서도 선택된 숫자 처리

    cout << "컴퓨터 선택 : " << nSelect << endl;
    Sleep(1000);
}

void ComSelect2(int* userTable, int* comTable) {
    
    int nIndex = 0;
    int nSelect;

    cout << "컴퓨터 선택 중";
    Sleep(333);
    cout << ".";
    Sleep(333);
    cout << ".";
    Sleep(333);
    cout << "." << endl;


    /*
    {4,1,1,1,4},
    {0,3,1,3,0},
    {0,0,5,0,0},
    {0,3,1,3,0},
    {3,0,1,0,3}
    */
    int nPritable[5][5] = {//우선순위 테이블 초기화
    {3,0,0,0,3},
    {0,3,0,3,0},
    {0,0,4,0,0},
    {0,3,0,3,0},
    {3,0,0,0,3}
    };

    for (int i = 0; i < 25; i++)//스캐닝 하기
    {
        if (userTable[i] == 0) {//만약 유저테이블의 값이 0이면
            nPritable[i / 5][i % 5] += 100; //우선순위 테이블의 값을 엄청 높은 수로 함과 동시에
            for (int j = 0; j < 5; j++) //우선순위 테이블의 가로,세로,대각선을 1만큼 더한다.
            {
                nPritable[i / 5][j]++;
                nPritable[j][i % 5]++;
                if (i % 6 == 0)
                {
                    nPritable[j][j]++;
                }
                if (i % 4 == 0 && i > 0)
                {
                    nPritable[j][4 - j]++;
                }
            }
        }
    }
    
    int nMin = 50;//최솟값 선언
    for (int i = 0; i < 25; i++)
    {
        if (nMin > nPritable[i / 5][i % 5]) {
            nMin = nPritable[i / 5][i % 5];//최솟값(가장 낮은 우선순위)를 해당 칸의 우선순위만큼 내려줌. 플레이어를 방해해야 하기 때문
        }
    }

    bool nHighstArray[25]{ 0, };

    for (int i = 0; i < 25; i++)//배열에 '최솟값이 들어있는 인덱스 번호'를 넣어줌.
    {
        if (nPritable[i / 5][i % 5] == nMin) {
            nHighstArray[i] = i;
        }
    }

    for (int i = 0; i < 625; i++) //그것을 마구 섞기
    {
        int nTemp;
        int nSrc = rand() % 25;
        int nDest = rand() % 25;

        nTemp = nHighstArray[nSrc];
        nHighstArray[nSrc] = nHighstArray[nDest];
        nHighstArray[nDest] = nTemp;
    }

    for (int i = 0; i < 25; i++)
    {
        if (nHighstArray[i] != 0) {
            nIndex = nHighstArray[i];
        }
    }

    nSelect = userTable[nIndex];

    for (int i = 0; i < 25; i++)//유저 테이블에서 선택된 숫자를 처리하고
    {
        if (nSelect == comTable[i]) {
            comTable[i] = 0;
            break;
        }
    }

    userTable[nIndex] = 0;//컴퓨터 테이블에서도 선택된 숫자 처리

    cout << "컴퓨터 선택 : " << nSelect << endl;
    Sleep(1000);
}

int CheckBingo(int* table) {
    int nBingo = 0;

    //가로 5
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i * 5 + j] == 0) {
                if (j == 4)
                    nBingo++;
            }
            else
                break;
            
        }
    }

    //세로 5
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i + j * 5 ] == 0) {
                if (j == 4)
                    nBingo++;
            }
            else
                break;

        }
    }
    //오른쪽 사선[ 0 6 12 18 24]
    for (int i = 0; i < 5; i++)
    {
        if (table[i * 6] == 0) {
            if (i == 4)
                nBingo++;
        }
        else
            break;
    }
    //왼쪽 사선 [4 8 12 16 20]
    for (int i = 1; i <= 5; i++)
    {
        if (table[i * 4] == 0) {
            if (i == 5)
                nBingo++;
        }
        else
            break;
    }

    return nBingo;
}