#include "stdafx.h"

int rsp() {
    int nSel, nCom = rand() % 3;
    cout << "0.가위, 1.바위, 2.보 : ";
    cin >> nSel;

    cout << "플레이어 : " << nSel << " vs " << nCom << " : 컴퓨터" << endl;

    if (nSel == nCom) {
        cout << "가위바위보에서 비겼습니다." << endl;
        return 0;
    }

    else if ((nSel + 1) % 3 == nCom) {
        cout << "컴퓨터가 가위바위보에서 이겼습니다." << endl;
        return -1;
    }
    else
    {
        cout << "플레이어가 가위바위보에서 이겼습니다." << endl;
        return 1;
    }
}

int main()
{
    srand(time(NULL));
    rand();

    bool isPlaying = true;
    int nPW = 0, nCW = 0;


    while (isPlaying) {

        int nAttacker = 0, nResult = 0;

        cout << "선공 정하기!" << endl;
        while (nAttacker == 0)
        {
            nAttacker = rsp();
        }
        if (nAttacker > 0) {
            cout << "플레이어의 선공!" << endl;
        }
        else {
            cout << "컴퓨터의 선공!" << endl;
        }

    
        while (true) {
            cout << endl;
            nResult = rsp();
            if (nResult == 0 && nAttacker < 0) {
                cout << "컴퓨터의 승리!" << endl;
                nCW++;
                cout << "플레이어 :" << nPW << " vs " << nCW << ": 컴퓨터"<<endl;
                break;
            }
            else if (nResult == 0 && nAttacker > 0) {
                cout << "플레이어의 승리!" << endl;
                nPW++;
                cout << "플레이어 :" << nPW << " vs " << nCW << ": 컴퓨터" << endl;
                break;
            }
            else if (nResult > 0) {
                cout << "이겼습니다! 플레이어의 공격 턴!" << endl;
                nAttacker = 1;
            }
            else if (nResult < 0) {
                cout << "졌습니다. 컴퓨터의 공격 턴!" << endl;
                nAttacker = -1;
            }
            else {
                cout << "버그 발생! 게임을 종료합니다." << endl;
                break;
            }
        }

        if (nCW >= 2) {
            cout << "컴퓨터의 최종 승리!" << endl;
            isPlaying = false;
        }
        else if (nPW >= 2) {
            cout << "플레이어의 최종 승리!" << endl;
            isPlaying = false;
        }
    }
    
    system("pause");

    return 0;
}
