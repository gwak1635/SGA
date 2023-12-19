#pragma once


//대기, 전투, 이동 enum문
enum E_PSTATE {P_IDLE, P_FIGHT, P_WALK};

enum E_ARMOR { A_EMPTY,  A_LIGHT, A_MEDIUM, A_HEAVY };

class cPlayer
{
private:
	string		m_strName;
	E_PSTATE	m_eState;
	int			m_nLevel;
	int			m_nExp;
	int			m_nMaxHp;
	int			m_nCurrHp;
	int			m_nAtt;
	E_ARMOR		m_eArmor;//현재 아머

	E_PLACE		m_eCurrPlace; // 현재 캐릭터의 장소

public:
	cPlayer();//생성자
	~cPlayer();//파괴자
	string GetName() { return m_strName; }
	E_PSTATE GetState() { return m_eState; }
	int GetLevel() { return m_nLevel; }
	int GetExp() { return m_nExp; }
	int GetMaxHP() { return m_nMaxHp; }
	int GetCurrHP() { return m_nCurrHp; }
	void SetMaxHP() { m_nCurrHp = m_nMaxHp; }
	int GetAttDamage() { return m_nAtt; }
	int GetExDamage() { return rand() % 6; }

	
	//플레이스 게터 세터
	E_PLACE GetPlace() { return m_eCurrPlace; }
	void SetPlace(E_PLACE place) { m_eCurrPlace = place; }
	
	void IncreaseExp(int exp);
	void CalcMaxHp();
	void TakeDamage(int damage) { m_nCurrHp -= damage; }
	
};

