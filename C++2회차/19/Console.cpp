// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include "stdafx.h"



struct tagMonster { //몬스터 구조체
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

    tagMonster stMonster; //구조체 선언 

    //구조체 값 설정
    stMonster.strName = "오우거";
    stMonster.nHp = 100;
    stMonster.nMp = 30;
    stMonster.nAtt = 10;
    stMonster.nDef = 5;
    
    cout << stMonster.strName.c_str() << "의 공격력은 " << stMonster.nAtt << "이다." << endl;   

    tagMonster stMonster1 = { "뱀파이어",50,100,25,0 };//구조체 선언 및 초기화

    cout << stMonster1.strName.c_str() << "의 공격력은 " << stMonster1.nAtt << "이다." << endl;
    
    tagMonster* pMonster;
    pMonster = new tagMonster;

    //pMonster = 주소
    //pMonster->strName
    //pMonster[0].strName = 값
    //*pMonster.strName 이건가? 아! 연산자!
    pMonster[0].strName = "트롤";
    pMonster->nHp = 100;
    (*pMonster).nMp = 100;
    pMonster->nAtt = 100;
    pMonster->nDef = 100;

    cout << pMonster->strName.c_str() << "의 공격력은 " << pMonster[0].nAtt << "이다." << endl;

    delete pMonster;

    tagMonster stMonsterArray[10];
    for (int i = 0; i < 10; i++) {
        stMonsterArray[i].strName = "오우거";
        stMonsterArray[i].nHp = 100 + rand() % 51;
        stMonsterArray[i].nMp = 30;
        stMonsterArray[i].nAtt = 10;
        stMonsterArray[i].nDef = 5;
    }

    //배열에 대한 동적할당

    tagMonster* aMonster = new tagMonster[10];
    aMonster[0].strName = "뱀파이어1";
    aMonster[1].strName = "뱀파이어2";
    delete[] aMonster;

    tagMonster* aMonster2;
    int nNumOfMon = 10 + rand() % 11;
    aMonster2 = new tagMonster[nNumOfMon];

    for (int i = 0; i < nNumOfMon; i++)
    {
        aMonster2[i].strName = "던전형 몬스터";
        aMonster2[i].nHp = 100 + rand() % 51;
        aMonster2[i].nMp = 30;
        aMonster2[i].nAtt = 10 + rand % 5;
        aMonster2[i].nDef = 5;

    }
    delete[] aMonster2;

    return 0;
}
