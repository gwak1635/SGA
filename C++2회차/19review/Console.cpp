// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

struct tagMonster {
    string  strName;
    int     nHp;
    int     nMp;
    int     nAtt;
    int     nDef;
};

int main()
{
    srand(time(NULL));
    rand();

    //구조체의 정적 할당. 스택 메모리에 쌓임.
    tagMonster stMonster;

    stMonster.strName = "오우거";
    stMonster.nHp = 100;
    stMonster.nMp = 25;
    stMonster.nAtt = 15;
    stMonster.nDef = 10;

    cout << stMonster.strName.c_str() << "의 공격력은 " << stMonster.nAtt << "이다.";

    tagMonster stMonster1 = { "뱀파이어", 50,50,30,0 };//정적 할당과 동시에 초기화

    cout << stMonster1.strName.c_str() << "의 공격력은 " << stMonster1.nAtt << "이다.";

    //동적 할당
    tagMonster* pMonster;
    pMonster = new tagMonster;

    pMonster->strName = "트롤";
    pMonster[0].nHp = 70;
    (*pMonster).nMp = 20;
    pMonster->nAtt = 20;
    pMonster->nDef = 7;

    cout << pMonster->strName.c_str() << "의 체력은 " << pMonster->nHp << "이다.";

    delete pMonster;

    //정적 할당 + 배열

    tagMonster stMonsterArray[10];
    for (int i = 0; i < 10; i++)
    {
        stMonsterArray[i].strName = "오우거";
        stMonsterArray[i].nHp = 100 + rand() % 51;
        stMonsterArray[i].nMp = 30;
        stMonsterArray[i].nAtt = 10;
        stMonsterArray[i].nDef = 5;
    }

    tagMonster* aMonster = new tagMonster[10];
    aMonster[0].strName = "뱀파이어";
    aMonster[1].strName = "뱀파이어";
    delete[] aMonster;

    tagMonster* aMonster2;
    int nNumOfMon = 10 + rand() % 11;
    aMonster2 = new tagMonster[nNumOfMon];

    for (int i = 0; i < 10; i++)
    {
        aMonster2[i].strName = "던전형 몬스터";
        aMonster2[i].nHp = 50 + rand() % 51;
        aMonster2[i].nMp = 30;
        aMonster2[i].nAtt = 10+ rand() % 6;
        aMonster2[i].nDef = 5;
    }
    delete[] aMonster;

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
