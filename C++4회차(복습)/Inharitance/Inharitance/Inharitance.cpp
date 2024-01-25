#include "stdafx.h"

class cWeapon //�θ� Ŭ����
{
private:

protected://��� ������ ����(�ڽ� Ŭ������ ���� ���� ����)
	int		m_nAttDamage;
	int		m_nDurability;

public:
	virtual void Attack() { //�����Լ�(�������: �����ͷ� ���� �� �������̵� ������ �ϱ� ����)
		cout << "�Ǽ� ����!" << endl;
	}
	virtual void Defence() {
		cout << "��ź ���!" << endl;
	}
};

class cSword : public cWeapon {
public:
	void Attack() override{
		cout << "������ ����!" << endl;
	}
	void Defence() override {
		cout << "������ ���!" << endl;
	}
};
class cShield : public cWeapon {
public:
	void Attack() override {
		cout << "���з� ����!" << endl;
	}
	void Defence() override{
		cout << "���з� ���!" << endl;
	}
};

int main() {

	cWeapon* pWeapon = new cSword;

	pWeapon->Attack();
	pWeapon->Defence();
	delete pWeapon;

	pWeapon = new cShield;
	pWeapon->Attack();
	pWeapon->Defence();
	delete pWeapon;

	return 0;
}