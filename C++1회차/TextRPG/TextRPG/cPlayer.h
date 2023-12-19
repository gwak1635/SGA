#pragma once


//���, ����, �̵�
enum E_PSTATE { P_IDLE, _FIGHT, P_WALK };

enum E_ARMOR {A_EMPTY, A_LIGHT, A_MEDIUM, A_HEAVY};

enum E_WEAPON {W_KNIFE, W_SWORD, W_HGUN, W_RIFLE };

class cPlayer
{
private:
	string m_strName;
	E_PSTATE m_eState;//��� ������ ��� m_�� ����.(���)
	int	m_nLevel;
	int	m_nExp;
	int	m_nMaxHp;
	int	m_nCurrHp;
	int	m_nAtt;
	E_ARMOR		m_eArmor; //���� ���� ����
	E_WEAPON	m_eWeapon; // ���� ���� ����

	E_PLACE m_eCurrPlace; //���� ĳ������ ���

public:
	cPlayer();//������
	~cPlayer();//�ı���
	//getter: Ŭ�������� ������� �����͸� �������� ���� �Լ�
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

	//�÷��̽� ���� ����
	E_PLACE GetPlace() { return m_eCurrPlace; }
	void SetPlace(E_PLACE place) { m_eCurrPlace = place; }
	//setter : Ŭ������ ������� �����͸� ����ֱ� ���� �Լ�(?)
	void IncreaseExp(int exp);
	void CalcMaxHp();
	void CalcAttDamage();

};

