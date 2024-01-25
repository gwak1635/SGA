#include "stdafx.h"
#include "cInventory.h"

void InitStore(cInventory& inven);

int main() {
	cInventory* pPlayerInven = new cInventory;
	cInventory* pStore = new cInventory;
	
	InitStore(*pStore);

	tagItem* buyItem = pStore->Delete("���۹���");
	if (buyItem != NULL) {
		pPlayerInven->Add(*buyItem);
		delete buyItem;
	}

	cout << "======== ���� ========" << endl;
	pStore->Show();
	cout << endl;

	cout << "======= �÷��̾� =======" << endl;
	pPlayerInven->Show();
	cout << endl;

	delete pPlayerInven;
	delete pStore;

	return 0;
}

void InitStore(cInventory& inven)
{
	tagItem stItem;

	stItem = tagItem(E_ARMOR, "���۹�");
	inven.Add(stItem);

	stItem = tagItem(E_WEAPON, "���۹���");
	inven.Add(stItem);

	stItem = tagItem(E_HP_POTION, "ü�¹���");
	inven.Add(stItem);

	stItem = tagItem(E_MP_POTION, "��������");
	inven.Add(stItem);
}
