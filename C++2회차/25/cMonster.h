#pragma once
class cMonster
{
private://m_멤버변수라는 뜻
	string      m_strName;	//이름
	int			m_nExp;		//경험치
	int			m_nMaxHp;	//최대 체력
	int			m_nCurrHp;	//현재 체력
	int			m_nAtt;		//공격력

public:
	//게터(Getter)클래스에서 멤버변수의 값을 가져오는 함수
	string GetName() { return m_strName; }
	int GetExp() { return m_nExp; }
	int GetMaxHp() { return m_nMaxHp; }
	int GetCurrHp() { return m_nCurrHp; }
	int GetAtt() { return m_nAtt; }

	void SetCurrHp(int Damage) { m_nCurrHp -= Damage; }

};

