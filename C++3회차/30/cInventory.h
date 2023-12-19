#pragma once

enum E_ITEM { E_ARMOR, E_WEAPON, E_HP_POTION, E_MP_POTION };

struct tagItem {
	E_ITEM itemType;
	string strName;
	int nPrice;

	tagItem() {};//생성자(구조체 선언 시 기본 생성자 필요)

	tagItem(E_ITEM _itemType, string _strName, int _nPrice) {
		itemType = _itemType;
		strName = _strName;
		nPrice = _nPrice;
	}
};

class cInventory
{
private:
	vector<tagItem>		m_vecItem;

public:
	cInventory();
	~cInventory();

	void Add(tagItem newItem);   //인벤토리에 아이템 넣기
	tagItem* Delete(string name);//인벤토리에서 아이템 꺼내기
	void Show();				 //인벤토리에 있는 아이템 목록 보여주기

};

