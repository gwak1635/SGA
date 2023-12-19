#include "stdafx.h"
#include "cInventory.h"

cInventory::cInventory()
{
}

cInventory::~cInventory()
{
}

void cInventory::Add(tagItem newItem)
{
	m_vecItem.push_back(newItem);
}

tagItem* cInventory::Delete(string name)
{
	tagItem* item = NULL;// 가방에 아이테이 없을 때 NULL

	vector<tagItem>::iterator vecIter;

	for (vecIter = m_vecItem.begin(); vecIter != m_vecItem.end(); vecIter++)
	{
		if (vecIter->strName == name)
		{
			item = new tagItem(vecIter->itemType, vecIter->strName);
			m_vecItem.erase(vecIter);
			break;
		}
	}

	return item;
}

void cInventory::Show()
{
	for (int i = 0; i < m_vecItem.size(); i++) {
		cout << "아이템 종류 : ";
		switch (m_vecItem[i].itemType)
		{
		case E_ARMOR:
			cout << "방어구" << endl;
			break;
		case E_WEAPON:
			cout << "무기" << endl;
			break;
		case E_HP_POTION:
			cout << "HP포션" << endl;
			break;
		case E_MP_POTION:
			cout << "MP포션" << endl;
			break;

			
		}
		cout << "아이템 이름 : " << m_vecItem[i].strName.c_str() << endl;
		cout << "==========================" << endl;
	}
}
