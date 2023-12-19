#include "stdafx.h"
#include "cPlayer.h"
#include "cMonster.h"
void Town(cPlayer* player, bool& playing);//레퍼런스, &이 이미 들어가 있다는 뜻
void Store(cPlayer* player);
void Dungeon(cPlayer* player);


int main()
{
    srand(time(NULL));
    rand();

    bool isPlaying = true;
    int nSelect;
    cPlayer* pPlayer = new cPlayer();//포인터 사용이 메모리 관리가 용이
    pPlayer->SetPlace(EP_TOWN);

    while (isPlaying)
    {
        system("cls");

        cout << "이름   : " << pPlayer->GetName().c_str() << endl;
        cout << "레벨   : " << pPlayer->GetLevel() << endl;
        cout << "경험치 : " << pPlayer->GetExp() << endl;
        cout << "체력   : " << pPlayer->GetCurrHP() << " / " << pPlayer->GetMaxHP() << endl;
        cout << "공격력 : " << pPlayer->GetAttDamage() << endl << endl;

        cout << "현재 위치 : ";
        switch (pPlayer->GetPlace())
        {
        case EP_QUIT:
            system("cls");
            cout << "게임을 종료합니다." << endl;
            isPlaying = false;
            break;
        case EP_TOWN:
            cout << "마을" << endl;
            Town(pPlayer,isPlaying);
            break;
        case EP_STORE:
            cout << "상점" << endl;
            Store(pPlayer);
            break;
        case EP_DUNGEON:
            cout << "슬라임 던전" << endl;
            Dungeon(pPlayer);
            break;
        case EP_DUNGEON2:
            cout << "오우거 던전" << endl;
            Dungeon(pPlayer);
            break;
        default:
            break;
        }

        Sleep(1500);
    }

    delete pPlayer;

    system("pause");

    return 0;
}

void Town(cPlayer* player, bool& playing)
{
    int nSelect;

    cout << "1.여관 2.상점 3.슬라임 던전 4.오우거 던전 (0.게임 종료) : ";
    cin >> nSelect;

    if (nSelect == 1)
    {
        cout << "휴식을 취합니다. HP 모두 회복!" << endl;
        player->SetMaxHP();
        cout << "마을로 돌아갑니다." << endl;
        player->SetPlace(EP_TOWN);//이 부분 약간 이해가 안대는데 원래 EP_TOWN아님?
    }
    else if (nSelect == 2)
    {
        cout << "상점으로 이동합니다." << endl;
        player->SetPlace(EP_STORE);
    }
    else if (nSelect == 3)
    {
        cout << "던전으로 이동합니다." << endl;
        player->SetPlace(EP_DUNGEON);
    }
    else if (nSelect == 4)
    {
        cout << "던전으로 이동합니다." << endl;
        player->SetPlace(EP_DUNGEON2);
    }
    else if (nSelect == 0) {
        player->SetPlace(EP_QUIT);
    }
    else {
        cout << "제대로 입력해라!!!!" << endl;
    }

}

void Store(cPlayer* player)
{
    cout << "상점에 주인이 없습니다. 마을로 돌아갑니다." << endl;
    player->SetPlace(EP_TOWN);
}

void Dungeon(cPlayer* player)
{
    cout << "슬라임 던전에 입장했습니다. 몬스터와 전투를 시작합니다." << endl;

    cMonster* pMonster = new cMonster();

    cout << "몬스터 이름 : " << pMonster->GetName().c_str() << endl;
    cout << "몬스터 체력 : " << pMonster->GetHp() << endl;
    cout << "몬스터 기본 공격력 : " << pMonster->GetAttDamage() << endl;
    cout << "============================================" << endl << endl;
    Sleep(2000);

    while (true) {
        int nDamage = player->GetAttDamage() + player->GetExDamage();
        cout << "플레이어가 공격합니다. : " << nDamage << endl;
        pMonster->TakeDamage(nDamage);
        Sleep(500);

        if (pMonster->GetHp() <= 0) {
            cout << "몬스터를 처치했습니다." << endl;
            cout << "경험치를 " << pMonster->GetExp() << "만큼 획득합니다." << endl;
            player->IncreaseExp(pMonster->GetExp());
            break;
        }

        nDamage = pMonster->GetAttDamage() + pMonster->GetExDamage();
        cout << "몬스터가 공격합니다. : " << nDamage << endl;
        player->TakeDamage(nDamage);
        Sleep(500);

        if (player->GetCurrHP() <= 0) {
            cout << "플레이어의 체력이 없습니다. 마을로 도망갑니다." << endl;
            break;
        }
    }
    Sleep(2000);

    player->SetPlace(EP_TOWN);

    delete pMonster;

}


void Dungeon2(cPlayer* player)
{
    cout << "오우거 던전에 입장했습니다. 몬스터와 전투를 시작합니다." << endl;

    cMonster* pMonster = new cMonster("오우거", 50, 20, 200);

    cout << "몬스터 이름 : " << pMonster->GetName().c_str()<<endl;
    cout << "몬스터 체력 : " << pMonster->GetHp() << endl;
    cout << "몬스터 기본 공격력 : " << pMonster->GetAttDamage() << endl;
    cout << "============================================" << endl << endl;
    Sleep(2000);

    while (true) {
        int nDamage = player->GetAttDamage() + player->GetExDamage();
        cout << "플레이어가 공격합니다. : " << nDamage << endl;
        pMonster->TakeDamage(nDamage);
        Sleep(500);

        if (pMonster->GetHp() <= 0) {
            cout << "몬스터를 처치했습니다." << endl;
            cout << "경험치를 " << pMonster->GetExp() << "만큼 획득합니다." << endl;
            player->IncreaseExp(pMonster->GetExp());
            break;
        }

        nDamage = pMonster->GetAttDamage() + pMonster->GetExDamage();
        cout << "몬스터가 공격합니다. : " << nDamage << endl;
        player->TakeDamage(nDamage);
        Sleep(500);

        if (player->GetCurrHP() <= 0) {
            cout << "플레이어의 체력이 없습니다. 마을로 도망갑니다." << endl;
            break;
        }
    }
    Sleep(2000);

    player->SetPlace(EP_TOWN);

    delete pMonster;

}
