
#include "stdafx.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_strName = "우주최강캐릭터";
	m_eState = P_IDLE;

	m_nExp = 0;
	m_nLevel = 1;

	m_eArmor = A_LIGHT;
	CalcMaxHp();
	m_nCurrHp = m_nMaxHp;

	m_eWeapon = W_KNIFE;
	CalcAttDamage();

}

cPlayer::~cPlayer()
{
}

void cPlayer::IncreaseExp(int exp)
{
	m_nExp += exp;
	if (m_nLevel * 100 < m_nExp)
		m_nLevel = m_nExp / 100 + 1;
}

void cPlayer::CalcMaxHp()//장비를 착용할 때 최대 체력 증가
{
	switch (m_eArmor)
	{
	case A_LIGHT:
		m_nMaxHp = 150;
		break;
	case A_MEDIUM:
		m_nMaxHp = 200;
		break;
	case A_HEAVY:
		m_nMaxHp = 300;
		break;
	default:
		m_nMaxHp = 100;
		break;
	}
}

void cPlayer::CalcAttDamage()
{
	switch (m_eWeapon)
	{
	case W_KNIFE:
		m_nAtt = 10;
		break;
	case W_SWORD:
		m_nAtt = 15;
		break;
	case W_HGUN:
		m_nAtt = 20;
		break;
	case W_RIFLE:
		m_nAtt = 30;
		break;
	default:
		break;
	}
}
