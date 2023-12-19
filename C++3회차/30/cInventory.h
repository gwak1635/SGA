#pragma once

enum E_ITEM { E_ARMOR, E_WEAPON, E_HP_POTION, E_MP_POTION };

struct tagItem {
	E_ITEM itemType;
	string strName;
	int nPrice;

	tagItem() {};//������(����ü ���� �� �⺻ ������ �ʿ�)

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

	void Add(tagItem newItem);   //�κ��丮�� ������ �ֱ�
	tagItem* Delete(string name);//�κ��丮���� ������ ������
	void Show();				 //�κ��丮�� �ִ� ������ ��� �����ֱ�

};

