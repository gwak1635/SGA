#include "stdafx.h"
#include "cInventory.h"

void cInventory::Add(tagItem newItem)
{
	m_vecItem.push_back(newItem);
}

tagItem* cInventory::Delete(string name)
{
	tagItem* item = NULL;
	
	vector<tagItem>::iterator vecIter;

	for (vecIter = m_vecItem.begin(); vecIter!= m_vecItem.end(); vecIter++)
	{
		if (vecIter->strName == name) {
			//item = &(*vecIter);
			item = new tagItem(vecIter->itemType, vecIter->strName);
			m_vecItem.erase(vecIter);
			break;
		}
	}

	return item;
}

void cInventory::Show()
{
	for (int i = 0; i < m_vecItem.size(); i++)
	{
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
			cout << "체력포션" << endl;
			break;
		case E_MP_POTION:
			cout << "마나포션" << endl;
			break;
		default:
			break;
		}
		
		cout << "아이템 이름 : " << m_vecItem[i].strName << endl;
		cout << "=============================" << endl;
	}
}
