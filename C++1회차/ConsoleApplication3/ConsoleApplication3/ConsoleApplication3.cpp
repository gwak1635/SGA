// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    rand();

    int nP, nC;
    bool isContinue = true;

    int nPw = 0, nCw = 0;

    while (isContinue) {
        cout << "1.가위 2.바위 3.보 : ";
        cin >> nP;

        nC = rand() % 3+1;

        if (nP == 1)
        {
            cout << "플레이어 - 가위 vs ";
            if (nC == 1)
            {
                cout << "가위 - 컴퓨터 : 무승부"<< endl;
            }
            else if (nC == 2) {
                cout << "바위 - 컴퓨터 : 컴퓨터 승" << endl;
                nCw++;
            }
            else {
                cout << "보 - 컴퓨터 : 플레이어 승" << endl;
                nPw++;
            }

        }
        else if (nP == 2) {
            cout << "플레이어 - 바위 vs ";
            if (nC == 1)
            {
                cout << "가위 - 컴퓨터 : 플레이어 승" << endl;
                nPw++;
            }
            else if (nC == 2) {
                cout << "바위 - 컴퓨터 : 무승부" << endl;
            }
            else {
                cout << "보 - 컴퓨터 : 컴퓨터 승" << endl;
                nCw++;
            }
        }
        else {
            cout << "플레이어 - 보 vs ";
            if (nC == 1)
            {
                cout << "가위 - 컴퓨터 : 컴퓨터 승" << endl;
                nCw++;
            }
            else if (nC == 2) {
                cout << "바위 - 컴퓨터 : 플레이어 승" << endl;
                nPw++;
            }
            else {
                cout << "보 - 컴퓨터 : 무승부" << endl;
            }
        }

        cout << "플레이어 - " << nPw << " vs " << nCw << " - 컴퓨터" << endl;

        if (nPw == 2) {
            cout << "플레이어 최종 승리!";
            isContinue = false;
        }
        else if (nCw == 2) {
            cout << "컴퓨터 최종 승리!";
            isContinue = false;
        }


    }


    //for (int i = 0; i < 5; i++) {
    //    //1. 변수 선언 및 초기화
    //    //2. 조건 검사
    //    //3. 알고리즘 실행
    //    //4. 증강값 적용
    //    //5. 2~4번 반복
    //    cout << "A값 입력 : ";
    //    cin >> nA;
    //    cout << "B값 입력 : ";
    //    cin >> nB;

    //    cout << "덧셈 결과 : " << nA + nB << endl;
    //}
    
    /*while (isContinue) {
        cout << "A값 입력 : ";
        cin >> nA;
        cout << "B값 입력 : ";
        cin >> nB;

        cout << "덧셈 결과 : " << nA + nB << endl;
        cout << " 0. 종료, 1. 계속 : ";
        cin >> isContinue;          
    }*/

    
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
