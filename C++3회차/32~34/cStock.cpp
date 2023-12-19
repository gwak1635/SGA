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
    m_vecItem[newItem.eType].push_back(newItem); //������ ������ �´� ���(����)�� �������� �߰�
}

tagItem cStock::PickItem(ITEM_TYPE itemType, int index)
{
    tagItem findItem;

    //�ش� ������ Ÿ���� �迭���� ���� �ε��� ��ġ�� �������� ã�´�.
    m_vecIter = m_vecItem[itemType].begin() + index;

    findItem = { m_vecIter->strName, m_vecIter->eType, m_vecIter->strDesc, m_vecIter->nAttribute, m_vecIter->nPrice };


    //ã�� �������� ������
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
            strType = "����";
            break;
        case ITEM_WEAPON:
            strType = "����";
            break;
        case ITEM_RING1:
            strType = "����1";
            break;
        case ITEM_RING2:
            strType = "����2";
            break;
        case ITEM_HP:
            strType = "ü�� ����";
            break;
        case ITEM_MP:
            strType = "���� ����";
        }
        cout << "=================================" << endl;
        cout << nNum << ". " << m_vecIter->strName << endl;
        cout << "������ ���� : " << strType << endl;
        cout << "������ ���� : " << m_vecIter->strDesc << endl;
        cout << "������ �Ӽ� : " << m_vecIter->nAttribute << endl;
        cout << "������ ���� : " << m_vecIter->nPrice << endl;
        cout << "=================================" << endl;

        nNum++;
    }
}
