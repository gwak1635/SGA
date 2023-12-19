#include "stdafx.h"
#include "cTown.h"

cTown::cTown()
{
}

cTown::~cTown()
{
}

void cTown::MainPlay(LOCATION& eCurrLoc)
{
	int nSelect;
	cout << "==================================" << endl;
	cout << "= C++마을에 오신 것을 환영합니다 =" << endl;
	cout << "==================================" << endl;
	cout << "= 1. 내 인벤토리 확인            =" << endl;
	cout << "= 2. 상점으로 가기               =" << endl;
	cout << "==================================" << endl;
	cout << ": ";
	cin >> nSelect;

	switch (nSelect) {
	case 1:
		eCurrLoc = LOCATION_INVENTORY;
		break;
	case 2:
		eCurrLoc = LOCATION_SHOP;
		break;
	default:
		eCurrLoc = LOCATION_TOWN;
		break;
	}

	//if (nSelect != 1 && nSelect != 2) {
	//	eCurrLoc = LOCATION_TOWN;
	//}
	//else
	//	eCurrLoc = (LOCATION)nSelect;

}
