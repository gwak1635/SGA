#pragma once

enum E_ITEM { E_ARMOR, E_WEAPON, E_HP_POTION, E_MP_POTION };

struct tagItem {
	E_ITEM itemType;
	string strName;

	tagItem() {};

	tagItem(E_ITEM _itemType, string _strName) {
		itemType = _itemType;
		strName = _strName;
	}
};

class cInventory
{
private:
	vector<tagItem> m_vecItem;

public:
	void Add(tagItem newItem);		//인벤에 템넣기
	tagItem* Delete(string name);	//인벤 꺼내기
	void Show();
};

