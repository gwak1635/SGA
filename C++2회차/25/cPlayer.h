#pragma once
//���, ����, �̵�
enum E_PSTATE {P_IDLE,P_FIGHT,P_WALK};

class cPlayer
{
private://m_���������� ��
	string      m_strName;	//�̸�
	E_PSTATE	m_eState;	//����
	int			m_nLevel;	//����
	int			m_nExp;		//����ġ
	int			m_nMaxHp;	//�ִ� ü��
	int			m_nCurrHp;	//���� ü��
	int			m_nAtt;		//���ݷ�

public:
	//����(Getter)Ŭ�������� ��������� ���� �������� �Լ�
	string GetName() { return m_strName; }
	E_PSTATE GetState() { return m_eState; }
	int GetLevel() { return m_nLevel; }
	int GetExp() { return m_nExp; }
	int GetMaxHp() { return m_nMaxHp; }
	int GetCurrHp() { return m_nCurrHp; }
	int GetAtt() { return m_nAtt; }

	void IncreaseExp(int exp); //����
	void CalcMaxHp();
	void CalcAttDamage();

};

