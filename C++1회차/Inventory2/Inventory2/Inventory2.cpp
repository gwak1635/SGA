// Inventory2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"
#include "cInventory.h"

void InitStore(cInventory* inven);

int main()
{
	cInventory* pPlayerInven  = new cInventory;
	cInventory* pStore = new cInventory;

	InitStore(pStore);

	tagItem* buyItem = pStore->Delete("슈퍼무기");
	if (buyItem != NULL) {
		pPlayerInven->Add(*buyItem);//여기서 new가 있으니까
		delete buyItem;
	}

	cout << " ========= 상점 =========" << endl;
	pStore->Show();
	cout << endl;

	cout << " ======== 플레이어 ========" << endl;
	pPlayerInven->Show();
	cout << endl;

	delete pStore;
	delete pPlayerInven;

	system("pause");
	return 0;
}

void InitStore(cInventory* inven)
{
	tagItem stItem;

	stItem = tagItem(E_ARMOR, "슈퍼방어구");
	inven->Add(stItem);

	stItem = tagItem(E_WEAPON, "슈퍼무기");
	inven->Add(stItem);

	stItem = tagItem(E_HP_POTION, "힐링포션");
	inven->Add(stItem);

	stItem = tagItem(E_MP_POTION, "마나물약");
	inven->Add(stItem);
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
