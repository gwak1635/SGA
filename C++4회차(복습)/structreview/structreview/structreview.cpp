#include <iostream>
#include <string>
#include <time.h>
using namespace std;

struct tagMonster   //몬스터 구조체
{
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

    cout << stMonster.strName.c_str() << "의 공격력은 " << stMonster.nAtt << " 이다." << endl;

    tagMonster stMonster1 = { "뱀파이어",50,100,25,1 };

    cout << stMonster1.strName.c_str() << "의 공격력은 " << stMonster1.nAtt << " 이다." << endl;

    tagMonster* pMonster;
    pMonster = new tagMonster;

    pMonster->strName = "트롤";
    pMonster->nHp = 100;

    delete pMonster;

    tagMonster stMonsterArray[10];
    for (int i = 0; i < 10; i++)
    {
        stMonsterArray[i].strName = "오우거";
        stMonsterArray[i].nHp = 100 + rand()%51;
        stMonsterArray[i].nMp = 30;
        stMonsterArray[i].nAtt = 10;
        stMonsterArray[i].nDef = 5;
    }

    tagMonster* aMonster = new tagMonster[10];
    
    aMonster[0].strName = "뱀파이어2";

    delete[] aMonster;
    
    system("pause");

    

    return 0;
}
