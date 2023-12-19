#include "stdafx.h"

struct tagMonster {//몬스터 구조체
	string	strName;
	int		nHp;
	int		nMp;
	int		nAtt;
	int		nDef;
};

int main()
{
	srand(time(NULL));

	tagMonster stMonster;

	//구조체 값 설정
	stMonster.strName = "오우거";
	stMonster.nHp = 100;
	stMonster.nMp = 30;
	stMonster.nAtt = 10;
	stMonster.nDef = 5;

	cout << stMonster.strName.c_str()<< "의 공격력은 " << stMonster.nAtt<<"이다."<<endl; //c형태 str로 변환

	tagMonster stMonster1 = { "뱀파이어",50,100,25,1 };

	cout << stMonster1.strName.c_str() << "의 공격력은 " << stMonster1.nAtt << "이다." << endl;

	//포인터를 이용한 동적 할당하기

	//tagMonster* pMonster = new tagMonster;

	tagMonster* pMonster;

	pMonster = new tagMonster;

	pMonster->strName = "트롤";
	(*pMonster).nHp = 100;//이딴식으로 될걸?

	delete pMonster;

	tagMonster stMonsterArr[10];
	for (int i = 0; i < 10; i++)
	{
		stMonsterArr[i].strName = "오우거";
		stMonsterArr[i].nHp = 100+rand()%51;
		stMonsterArr[i].nMp = 30;
		stMonsterArr[i].nAtt = 10;
		stMonsterArr[i].nDef = 5;
	}

	//배열에 대한 돌적 할당

	tagMonster* aMonster = new tagMonster[3];

	aMonster->strName = "뱀파이어2";
	(aMonster + 1)->strName = "뱀파이어3";
	aMonster[2].strName = "뱀파이어4";

	for (int i = 0; i < 3; i++)
	{
		cout << aMonster[i].strName << endl;
	}

	delete[] aMonster;

	int* pA = new int[10];

	for (int i = 0; i < 5; i++)
	{
		pA[i] = i;//*(pA+i)
		cout << pA[i] << endl;
	}
	for (int i = 5; i < 10; i++) {
		*(pA + i) = i;
		cout << pA[i] << endl;
	}

	delete[] pA;

	tagMonster* aMonster2;
	int nNumOfMon = 10 + rand() % 11;
	aMonster2 = new tagMonster[nNumOfMon];

	for (int i = 0; i < nNumOfMon; i++)
	{
		 aMonster2[i].strName = "던전형 몬스터";
		 aMonster2[i].nHp = 100 + rand() % 51;
		 aMonster2[i].nMp = 30;
		 aMonster2[i].nAtt = 10 + rand() % 6;
		 aMonster2[i].nDef = 5;
	}

	for (int i = 0; i < nNumOfMon; i++)
	{
		cout << "몬스터의 종류 : " << aMonster2[i].strName.c_str() << endl;
		cout << "몬스터의 체력 : " << aMonster2[i].nHp << endl;
		cout << "몬스터의 공격력 : " << aMonster2[i].nAtt << endl<<endl;
	}

	delete[] aMonster2;
	

	system("pause");
	return 0;
}
