#include "stdafx.h"
#include "cInventory.h"

void InitStore(cInventory& inven);

int main() {
	cInventory* pPlayerInven = new cInventory;
	cInventory* pStore = new cInventory;
	
	InitStore(*pStore);

	tagItem* buyItem = pStore->Delete("슈퍼무기");
	if (buyItem != NULL) {
		pPlayerInven->Add(*buyItem);
		delete buyItem;
	}

	cout << "======== 상점 ========" << endl;
	pStore->Show();
	cout << endl;

	cout << "======= 플레이어 =======" << endl;
	pPlayerInven->Show();
	cout << endl;

	delete pPlayerInven;
	delete pStore;

	return 0;
}

void InitStore(cInventory& inven)
{
	tagItem stItem;

	stItem = tagItem(E_ARMOR, "슈퍼방어구");
	inven.Add(stItem);

	stItem = tagItem(E_WEAPON, "슈퍼무기");
	inven.Add(stItem);

	stItem = tagItem(E_HP_POTION, "체력물약");
	inven.Add(stItem);

	stItem = tagItem(E_MP_POTION, "마나물약");
	inven.Add(stItem);
}
