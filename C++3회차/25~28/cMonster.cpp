#include "stdafx.h"
#include "cMonster.h"

cMonster::cMonster()//직접 구현
{
	m_strName = "슬라임";
	m_nHp = 50;
	m_nAtt = 5+rand()%11;
	m_nExp = 50;
}

cMonster::cMonster(string name, int hp, int att, int exp)//간접 구현
{
	m_strName = name;
	m_nHp = hp;
	m_nAtt = att;
	m_nExp = exp;
}

cMonster::~cMonster()
{
}

