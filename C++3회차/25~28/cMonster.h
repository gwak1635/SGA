#pragma once
class cMonster
{
private:
	string		m_strName;
	int			m_nHp;
	int			m_nAtt;
	int			m_nExp;
public:
	cMonster();
	cMonster(string name, int hp, int att, int exp);
	~cMonster();
	string GetName() { return m_strName; }
	int GetHp() { return m_nHp; }
	int GetAttDamage() { return m_nAtt; }
	int GetExDamage() { return rand() % 10; }
	int GetExp() { return m_nExp;}

	void TakeDamage(int damage) { m_nHp -= damage; }
};

