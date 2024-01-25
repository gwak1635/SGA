#include "stdafx.h"

class cWeapon //부모 클래스
{
private:

protected://상속 가능한 내용(자식 클래스를 통해 접근 가능)
	int		m_nAttDamage;
	int		m_nDurability;

public:
	virtual void Attack() { //가상함수(사용이유: 포인터로 선언 시 오버라이딩 가능케 하기 위해)
		cout << "맨손 공격!" << endl;
	}
	virtual void Defence() {
		cout << "육탄 방어!" << endl;
	}
};

class cSword : public cWeapon {
public:
	void Attack() override{
		cout << "검으로 공격!" << endl;
	}
	void Defence() override {
		cout << "검으로 방어!" << endl;
	}
};
class cShield : public cWeapon {
public:
	void Attack() override {
		cout << "방패로 공격!" << endl;
	}
	void Defence() override{
		cout << "방패로 방어!" << endl;
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