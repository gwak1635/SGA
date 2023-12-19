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

    tagMonster stMonster;

    stMonster.strName = "오우거";
    stMonster.nHp = 100;
    stMonster.nMp = 30;
    stMonster.nAtt = 10;
    stMonster.nDef = 5;

    cout << stMonster.strName.c_str() << "의 공격력은" << stMonster.nAtt << "이다." << endl;

    tagMonster stMonster1{ "뱀파이어",50,100,30,0 };

    cout << stMonster1.strName.c_str() << "의 공격력은" << stMonster1.nAtt << "이다." << endl;

    tagMonster* pMonster;

    pMonster = new tagMonster;

    pMonster->strName = "트롤";
    (*pMonster).nHp = 100;

    delete pMonster;

    tagMonster stMonsterArr[10];

    for (int i = 0; i < 10; i++)
    {
        stMonsterArr[i].strName = "오우거";
        stMonsterArr[i].nHp = 100+rand()%51;
        stMonsterArr[i].nMp = 30;
        stMonsterArr[i].nAtt = 10+rand()%6;
        stMonsterArr[i].nDef = 5;
    }

    tagMonster* pMonsterArr= new tagMonster[3];

    pMonsterArr[0].strName = "뱀파이어2";
    (pMonsterArr+1)->strName = "뱀파이어3";
    (*(pMonsterArr+2)).strName = "뱀파이어4";//히히 트롤링!

    for (int i = 0; i < 3; i++)
    {
        cout << pMonsterArr[i].strName << endl;
    }

    delete[] pMonsterArr;

    tagMonster* aMonster;

    int nNumOfMon = 10 + rand() % 11;
    cout << "소환된 몬스터의 수 : " << nNumOfMon << endl;

    aMonster = new tagMonster[nNumOfMon];

    for (int i = 0; i < nNumOfMon; i++)
    {
        aMonster[i].strName = "던전형 몬스터";
        aMonster[i].nHp = 100 + rand() % 51;
        aMonster[i].nMp = 30;
        aMonster[i].nAtt = 10 + rand() % 6;
        aMonster[i].nDef = 5;
    }

    for (int i = 0; i < nNumOfMon; i++)
    {
        cout<< "몬스터의 이름 : "<< aMonster[i].strName.c_str()<<endl;
        cout<< "몬스터의 체력 : "<< aMonster[i].nHp<<endl;
        cout << "몬스터의 공격력 : " << aMonster[i].nMp << endl << endl;;
    }

    delete[] aMonster;

    system("pause");
    return 0;
}
