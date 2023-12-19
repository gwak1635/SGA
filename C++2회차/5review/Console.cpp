// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"
int rsp() {
    int nPlayer;
    char chScissor[] = "가위";
    char chRock[] = "바위";
    char chPaper[] = "보";

    cout << "0.가위 1.바위 2.보 : ";
    cin >> nPlayer;
    int nCom = rand() % 3; // 0 가위 1 바위 2 보;

    cout << "컴퓨터: ";
    if (nCom == 0)      cout << chScissor;
    else if (nCom == 1) cout << chRock;
    else                cout << chPaper;
    cout << " vs ";
    if (nPlayer == 0)       cout << chScissor;
    else if (nPlayer == 1)  cout << chRock;
    else                    cout << chPaper;
    cout << " :플레이어" << endl;

    // 0 < 1 1 <2 2<0
    if (nCom == nPlayer)
        return 0;
    else if ((nCom + 1) % 3 == nPlayer)
        return 1;
    else
        return -1;
}


int main()
{
    srand(time(NULL));
    rand();

    bool isPlaying = true;
    int nAtt = 0;
    int nMjp = 0;
    int nP = 0, nC = 0;


    while (true) {
        
        while (nAtt == 0) {
            nAtt = rsp();
            if (nAtt == 1) {
                cout << "플레이어가 공격!" << endl;
            }
            else if (nAtt == -1)
                cout << "컴퓨터가 공격!" << endl;
            else
                cout << "무승부!" << endl;
        }
        isPlaying = true;
        while (isPlaying == true) {
            cout << "==================================" << endl;
            if (nAtt == 1) {
                nAtt = rsp();
                if (nAtt == 0) {
                    cout << "플레이어 승리!" << endl;
                    nP++;
                    isPlaying = false;
                }
                else if (nAtt == 1) {
                    cout << "플레이어가 계속 공격!" << endl;
                }
                else
                    cout << "컴퓨터의 공격!" << endl;
            }
            else if (nAtt == -1) {
                nAtt = rsp();
                if (nAtt == 0) {
                    cout << "컴퓨터의 승리!" << endl;
                    isPlaying = false;
                    nC++;
                }
                else if (nAtt == 1) {
                    cout << "플레이어의 공격!" << endl;
                }
                else
                    cout << "컴퓨터가 계속 공격!" << endl;
            }
        }
        cout << "점수 [플레이어 : " << nP << " vs " << nC << " : 컴퓨터]" << endl;
        if (nP >= 2) {
            cout << "플레이어 최종 승리!";
            break;
        }
        if (nC >= 2) {
            cout << "컴퓨터의 최종 승리!";
            break;
        }
    }
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
