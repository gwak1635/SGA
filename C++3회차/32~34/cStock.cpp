#include "stdafx.h"
#include "cStock.h"

cStock::cStock()
{
}

cStock::~cStock()
{
}

void cStock::AddItem(tagItem newItem)
{
    m_vecItem[newItem.eType].push_back(newItem); //아이템 종류에 맞는 목록(벡터)에 아이템을 추가
}

tagItem cStock::PickItem(ITEM_TYPE itemType, int index)
{
    tagItem findItem;

    //해당 아이템 타입의 배열에서 선택 인덱스 위치의 아이템을 찾는다.
    m_vecIter = m_vecItem[itemType].begin() + index;

    findItem = { m_vecIter->strName, m_vecIter->eType, m_vecIter->strDesc, m_vecIter->nAttribute, m_vecIter->nPrice };


    //찾은 아이템은 삭제함
    m_vecItem[itemType].erase(m_vecIter);

    return findItem;
}

vector<tagItem>& cStock::GetItemList(ITEM_TYPE itemType)
{
    return m_vecItem[itemType];
}

void cStock::ShowItem(ITEM_TYPE itemType)
{
    int nNum = 1;
    string strType;

    for (m_vecIter = m_vecItem[itemType].begin(); m_vecIter != m_vecItem[itemType].end(); m_vecIter++) {
        switch (m_vecIter->eType)
        {
        case ITEM_ARMOR:
            strType = "갑옷";
            break;
        case ITEM_WEAPON:
            strType = "무기";
            break;
        case ITEM_RING1:
            strType = "반지1";
            break;
        case ITEM_RING2:
            strType = "반지2";
            break;
        case ITEM_HP:
            strType = "체력 물약";
            break;
        case ITEM_MP:
            strType = "마나 물약";
        }
        cout << "=================================" << endl;
        cout << nNum << ". " << m_vecIter->strName << endl;
        cout << "아이템 종류 : " << strType << endl;
        cout << "아이템 설명 : " << m_vecIter->strDesc << endl;
        cout << "아이템 속성 : " << m_vecIter->nAttribute << endl;
        cout << "아이템 가격 : " << m_vecIter->nPrice << endl;
        cout << "=================================" << endl;

        nNum++;
    }
}
