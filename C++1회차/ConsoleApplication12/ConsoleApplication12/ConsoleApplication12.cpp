// ConsoleApplication12.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void InitTable(int* table);
void ShowTable(int* table);
void HideTable(int* table);
void UserSelect(int* userTable, int* comTable);
void ComSelect(int* userTable, int* comTable);
int CheckBingo(int* table);

int main(){

    //랜덤 초기화
    srand(time(NULL));
    rand();


    //테이블 배열과 빙고 변수 선언
    int nUserTable[25];
    int nUserBingo = 0;
    int nComTable[25];
    int nComBingo = 0;

    //게임 진행 변수 선언
    bool isPlaying = true;
    bool isMyTurn = true;

    //게임 진행
    while (isPlaying) {
        // 플레이
        InitTable(nUserTable);
        InitTable(nComTable);
        nUserBingo = CheckBingo(nUserTable);
        nComBingo = CheckBingo(nComTable);

        while (true) {
            system("cls");

            //nUserBingo < 3 && nComBingo < 3
            
            //테이블 확인
            HideTable(nComTable);
            cout << "컴퓨터 빙고 : " << nComBingo << endl<<endl;
            ShowTable(nUserTable);
            cout << "유저 빙고 : " << nUserBingo << endl;
            //빙고 확인
            nUserBingo = CheckBingo(nUserTable);
            nComBingo = CheckBingo(nComTable);
            

            if (nComBingo >= 3 && nUserBingo >= 3) {
                cout << "무승부!" << endl;
                Sleep(2000);
                break;
            }
            else if (nUserBingo >= 3) {
                cout << "플레이어 승리!" << endl;
                Sleep(2000);
                break;
            }
            else if (nComBingo >= 3) {
                cout << "컴퓨터의 승리!" << endl;
                Sleep(2000);
                break;
            }
            if (isMyTurn == true) {
                UserSelect(nUserTable, nComTable);
                isMyTurn = false;
            }
            else {
                ComSelect(nUserTable, nComTable);
                isMyTurn = true;
            }
            //여기에 대충 빙고 인식 코드
            
        }
        

        // 게임 종료 선택
        cout << "0.게임 종료, 1.새 게임 : ";
        cin >> isPlaying;
    }

    return 0;
}

void InitTable(int* table){
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


void ShowTable(int* table){
    cout << "=========================================" << endl;
    for (int i = 0; i < 25; i++) {
        cout << "|  " << table[i] << "\t|";
        
        if(i % 5 == 4) {
            cout << endl;
            cout << "=========================================" << endl;
        }
    }
}
void HideTable(int* table) {
    cout << "=========================================" << endl;
    for (int i = 0; i < 25; i++) {
        if (table[i]==0)
            cout << "|  0\t|";
        else
            cout << "|  ?\t|";
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

    for (int i = 0; i < 25; i++) {
        if (nSelect == userTable[i])
        {
            // 0은 테이블에서 이미 선택된 숫자를 의미
            userTable[i] = 0;
            for (int j = 0; j < 25; j++) {
                if (nSelect == comTable[j])
                {
                    // 0은 테이블에서 이미 선택된 숫자를 의미
                    comTable[j] = 0;
                    break;
                }

            }
            break;
        }
        
        // 선택한 숫자를 찾지 못한 경우
        if (i == 24)
        {
            cout << "제대로 선택해라!!" << endl;
            Sleep(1000);
        }

    }
}
/*
[3] [ ] [ ] [ ] [3]
[ ] [3] [ ] [3] [ ]
[ ] [ ] [4] [ ] [ ]
[ ] [3] [ ] [3] [ ]
[3] [ ] [ ] [ ] [3]
*/
void ComSelect(int* userTable, int* comTable) {

    int nIndex = 0;

    cout << "컴퓨터 선택 중";
    Sleep(300);
    cout << ".";
    Sleep(300);
    cout << ".";
    Sleep(300);
    cout << "." << endl;


    while (true) {
        nIndex = rand() % 25;

        if (comTable[nIndex] != 0)
        {
            cout << "컴퓨터의 선택 : " << comTable[nIndex] << endl;

           
            for (int i = 0; i < 25; i++) {
                if (comTable[nIndex] == userTable[i])
                {
                    userTable[i] = 0;
                    break;
                }

            }

            comTable[nIndex] = 0;
            Sleep(2000);
            break;
        }
            
        
    }
}

int CheckBingo(int* table) {
    int nBingo = 0;

    //가로검사
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i * 5 + j] == 0)//한칸씩 선택 유무 확인
            {
                if (j == 4)//제일 마지막칸까지 선택이 되어 있는 경우
                    nBingo++;
            }
            else
                break;
        }
    }

    //세로검사
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i + j * 5] == 0)//한칸씩 선택 유무 확인
            {
                if (j == 4)//제일 마지막칸까지 선택이 되어 있는 경우
                    nBingo++;
            }
            else
                break;
        }
    }


    //좌상 우하
    for (int i = 0; i < 5; i++)
    {
        if (table[i*6] == 0)//한칸씩 선택 유무 확인
        {
            if (i == 4)//제일 마지막칸까지 선택이 되어 있는 경우
                nBingo++;
        }
        else
            break;
    }
    //우상 좌하
    for (int i = 1; i < 6; i++)
    {
        if (table[i * 4] == 0)//한칸씩 선택 유무 확인
        {
            if (i == 5)//제일 마지막칸까지 선택이 되어 있는 경우
                nBingo++;
        }
        else
            break;
    }

    return nBingo;
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
