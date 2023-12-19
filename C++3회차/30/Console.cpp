#include "stdafx.h"
#include "cInventory.h"

void InitStore(cInventory* inven);
void BuyItem(cInventory* playerinven, cInventory* store, string item, int& money);
void SellItem(cInventory* playerinven, cInventory* store, string item, int& money);

int main()
{
    cInventory* pPlayerInven = new cInventory;
    cInventory* pStore = new cInventory;
    bool isInstore = true;
    InitStore(pStore);
    int nMymoney = 500;

    while (isInstore) {
        int nSelect;
        string strSelect;

        system("cls");

        cout << "========= 상점 =========" << endl;
        pStore->Show();
        cout << endl;

        cout << "======= 플레이어 =======" << endl;
        pPlayerInven->Show();
        cout << endl;

        cout << "현재 보유액 : " << nMymoney << endl;
        cout << "0.나가기 1.구매 2.판매 : ";
        cin >> nSelect;

        if (nSelect == 0) {
            isInstore = false;
        }
        else if (nSelect == 1) {
            cout << "구매할 물건의 이름을 입력하시오 : ";
            cin >> strSelect;
            BuyItem(pPlayerInven, pStore, strSelect, nMymoney);
        }
        else if (nSelect == 2) {
            cout << "판매할 물건의 이름을 입력하시오 : ";
            cin >> strSelect;
            SellItem(pPlayerInven, pStore, strSelect, nMymoney);
        }
        else {
            cout << "제대로 입력해라!!" << endl;
            Sleep(2000);
        }
    }


    delete pPlayerInven;
    delete pStore;

    system("pause");

    return 0;
}

void InitStore(cInventory* inven)
{
    tagItem stItem;

    stItem = tagItem(E_ARMOR, "슈퍼방어구", 1000);
    inven->Add(stItem);

    stItem = tagItem(E_WEAPON, "슈퍼무기", 1000);
    inven->Add(stItem);

    stItem = tagItem(E_HP_POTION, "힐물약", 100);
    inven->Add(stItem);

    stItem = tagItem(E_MP_POTION, "마나물약", 50);
    inven->Add(stItem);
}

void BuyItem(cInventory* playerinven, cInventory* store, string item, int& money)
{
    tagItem* buyItem = store->Delete(item);
    if (buyItem != NULL)
    {

        if (money >= buyItem->nPrice) {
            money -= buyItem->nPrice;
            playerinven->Add(*buyItem);
            delete buyItem;//Delete함수에 new가 있었음.
        }
        else {
            cout << "잔액이 부족합니다. 상점에 물건을 되돌려 놓습니다." << endl;
            store->Add(*buyItem);
            delete buyItem;
            Sleep(2000);
        }
    }

}

void SellItem(cInventory* playerinven, cInventory* store, string item, int& money)
{
    tagItem* buyItem = playerinven->Delete(item);
    if (buyItem != NULL)
    {
        money += (buyItem->nPrice)/2;
        store->Add(*buyItem);
        delete buyItem;//Delete함수에 new가 있었음.
    }

}