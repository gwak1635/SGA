#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
	m_strName="Hex";
	m_eState = P_IDLE;

	m_nExp = 0;
	m_nLevel =1;
	
	m_eArmor = A_LIGHT;
	CalcMaxHp();

	m_nCurrHp = m_nMaxHp;
	m_nAtt = 5;
}

cPlayer::~cPlayer()
{
}

void cPlayer::IncreaseExp(int exp)
{
	m_nExp += exp;

	if (m_nExp > m_nLevel * 100) {
		m_nLevel = m_nExp / 100 +1 ;
		m_nAtt = 5 * m_nLevel;
		CalcMaxHp();
	}
}

void cPlayer::CalcMaxHp()
{
	switch (m_eArmor)
	{
	case A_LIGHT:
		m_nMaxHp = 100+m_nLevel*50;
		break;
	case A_MEDIUM:
		m_nMaxHp = 150 + m_nLevel * 50;
		break;
	case A_HEAVY:
		m_nMaxHp = 200 + m_nLevel * 50;
		break;
	default:
		m_nMaxHp = 50 + m_nLevel * 50;
		break;
	}
}
