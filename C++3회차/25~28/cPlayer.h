#pragma once


//���, ����, �̵� enum��
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
	E_ARMOR		m_eArmor;//���� �Ƹ�

	E_PLACE		m_eCurrPlace; // ���� ĳ������ ���

public:
	cPlayer();//������
	~cPlayer();//�ı���
	string GetName() { return m_strName; }
	E_PSTATE GetState() { return m_eState; }
	int GetLevel() { return m_nLevel; }
	int GetExp() { return m_nExp; }
	int GetMaxHP() { return m_nMaxHp; }
	int GetCurrHP() { return m_nCurrHp; }
	void SetMaxHP() { m_nCurrHp = m_nMaxHp; }
	int GetAttDamage() { return m_nAtt; }
	int GetExDamage() { return rand() % 6; }

	
	//�÷��̽� ���� ����
	E_PLACE GetPlace() { return m_eCurrPlace; }
	void SetPlace(E_PLACE place) { m_eCurrPlace = place; }
	
	void IncreaseExp(int exp);
	void CalcMaxHp();
	void TakeDamage(int damage) { m_nCurrHp -= damage; }
	
};

