#pragma once
class cMonster
{
private://m_���������� ��
	string      m_strName;	//�̸�
	int			m_nExp;		//����ġ
	int			m_nMaxHp;	//�ִ� ü��
	int			m_nCurrHp;	//���� ü��
	int			m_nAtt;		//���ݷ�

public:
	//����(Getter)Ŭ�������� ��������� ���� �������� �Լ�
	string GetName() { return m_strName; }
	int GetExp() { return m_nExp; }
	int GetMaxHp() { return m_nMaxHp; }
	int GetCurrHp() { return m_nCurrHp; }
	int GetAtt() { return m_nAtt; }

	void SetCurrHp(int Damage) { m_nCurrHp -= Damage; }

};

