// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

/*
숫자 야구 게임
1~9까지의 숫자 중 랜덤한 숫자 3개(중복 허용인지 아닌지는 모름)가 선택이 되고 그 숫자3개를 맞히는 게임
1. 컴퓨터가 임의의 숫자 3개를 '순차적으로' 선택. ex) 6 2 3
2. 숫자 3개를 '순차적'으로 고름. ex) 2 0 3
3. 숫자의 위치가 다르면 볼, 같으면 스트라이크, 없으면 아웃(볼 아웃 스트라이크)
출력
스트라이크 : 1
볼 : 1
아웃 : 1
-반복-


*/

enum E_JUDGE { E_STRIKE, E_BALL, E_OUT, E_MAX };

int main()
{
    srand(time(NULL));
    rand();

    bool isPlaying = true;


    //int nArray[10];
    //for (int i = 0; i < 10; i++) {
    //    nArray[i] = i;
    //}

    //for (int i = 0; i < 150; i++)
    //{
    //    int nSrc = rand()%10;
    //    int nDest = rand()%10;
    //    int nTemp;

    //    nTemp = nArray[nSrc];
    //    nArray[nSrc] = nArray[nDest];
    //    nArray[nDest] = nTemp;
    //    
    //}

    //nA = nArray[0];
    //nB = nArray[1];
    //nC = nArray[2];


    while (isPlaying) {
        int nTry = 0;
        int nA, nB, nC;
        int nPA, nPB, nPC;

        nA = rand() % 10;  //7선택 가정
        nB = rand() % 9;   //0 1 2 3 4 5 6 7 8까지 선택됨.
        if (nB >= nA)      //7,8이 선택될 경우
            nB++;          //8,9로 옮겨주기
        nC = rand() % 8;  //6 7 이 선택되었다 가정
        if (nC >= nB)      //6 선택
            nC++;
        if (nC >= nA)
            nC++;

        E_JUDGE eJudge = E_STRIKE;
        int nJudge[E_MAX] = { 0, };

        while (nJudge[E_STRIKE] < 3) {
            for (int i = 0; i < E_MAX; i++)
            {
                nJudge[i] = 0;
            }


            nTry++;

            cout << "첫 번째 숫자를 입력하시오 : ";
            cin >> nPA;
            cout << "두 번째 숫자를 입력하시오 : ";
            cin >> nPB;
            cout << "세 번째 숫자를 입력하시오 : ";
            cin >> nPC;

            if (nPA == nA) {
                nJudge[E_STRIKE]++;
            }
            else if (nPA == nB || nPA == nC) {
                nJudge[E_BALL]++;
            }
            else
                nJudge[E_OUT]++;
            if (nPB == nB) {
                nJudge[E_STRIKE]++;
            }
            else if (nPB == nA || nPB == nC) {
                nJudge[E_BALL]++;
            }
            else
                nJudge[E_OUT]++;
            if (nPC == nC) {
                nJudge[E_STRIKE]++;
            }
            else if (nPC == nA || nPC == nB) {
                nJudge[E_BALL]++;
            }
            else
                nJudge[E_OUT]++;

            cout << "스트라이크 : " << nJudge[E_STRIKE] << endl;
            cout << "볼 : " << nJudge[E_BALL] << endl;
            cout << "아웃 : " << nJudge[E_OUT] << endl;
            cout << "시도 횟수 : " << nTry << endl;
        }
        cout << "숫자를 모두 맞혔으므로 게임을 종료합니다." << endl;
        cout << "계속하시겠습니까? (아니오: 0, 예: 1) : ";
        cin >> isPlaying;
        cout << endl;
    }

    system("pause");

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
