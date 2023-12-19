#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
{
	m_pPlayer = new cPlayer("플레이어");
	m_eCurrLoc = LOCATION_TOWN;//캐릭터의 위치 정보

	m_pTown= new cTown;
	m_pShop = new cShop;
}

cMainGame::~cMainGame()
{
	delete m_pPlayer;
	delete m_pTown;
	delete m_pShop;
}

void cMainGame::MainPlay()
{
	system("cls");

	switch (m_eCurrLoc)
	{
	case LOCATION_TOWN:
		m_pTown->MainPlay(m_eCurrLoc);
		break;
	case LOCATION_SHOP:
		m_pShop->MainPlay(m_eCurrLoc, m_pPlayer->GetInventory());
		break;
	case LOCATION_INVENTORY:
		m_pPlayer->ShowAllItem();
		m_eCurrLoc = LOCATION_TOWN;
		break;
	}
}
