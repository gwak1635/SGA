#pragma once


//대기, 전투, 이동
enum E_PSTATE { P_IDLE, _FIGHT, P_WALK };

enum E_ARMOR {A_EMPTY, A_LIGHT, A_MEDIUM, A_HEAVY};

enum E_WEAPON {W_KNIFE, W_SWORD, W_HGUN, W_RIFLE };

class cPlayer
{
private:
	string m_strName;
	E_PSTATE m_eState;//멤버 변수의 경우 m_을 붙임.(약식)
	int	m_nLevel;
	int	m_nExp;
	int	m_nMaxHp;
	int	m_nCurrHp;
	int	m_nAtt;
	E_ARMOR		m_eArmor; //현재 장착 무기
	E_WEAPON	m_eWeapon; // 현재 장착 무기

	E_PLACE m_eCurrPlace; //현재 캐릭터의 장소

public:
	cPlayer();//생성자
	~cPlayer();//파괴자
	//getter: 클래스에서 멤버변수 데이터를 가져오기 위한 함수
	string GetName(){ return m_strName; }
	E_PSTATE GetState(){ return m_eState; }
	int GetLevel(){ return m_nLevel; }
	int GetExp(){ return m_nExp; }
	int GetMaxHp(){ return m_nMaxHp; }
	int GetCurrHP(){ return m_nCurrHp; }
	void SetMaxHP() { m_nCurrHp = m_nMaxHp; }
	int GetAttDamage(){ return m_nAtt; }
	int GetExDamage() { return rand() % 11; }
	void TakeDamage(int damage) { m_nCurrHp -= damage; }

	//플레이스 게터 세터
	E_PLACE GetPlace() { return m_eCurrPlace; }
	void SetPlace(E_PLACE place) { m_eCurrPlace = place; }
	//setter : 클래스에 멤버변수 데이터를 집어넣기 위한 함수(?)
	void IncreaseExp(int exp);
	void CalcMaxHp();
	void CalcAttDamage();

};

