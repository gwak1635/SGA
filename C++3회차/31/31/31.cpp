#include "stdafx.h"

/*
클래스에서 상속이란?
부모 클래스로부터 자식 클래스로 변수 또는 함수를 물려주는 시스템
*/

/*
virtual funtion(가상 함수)
C++에는 다형성이라는 특성을 지원하기 위해 virtual 키워드 제공
부모 클래스 내에서 virtual로 선언된 함수는 자식 클래스에서 재정의될 수 있음[오버라이딩]
재정의를 하지 않고 호출되면 부모의 함수가 호출됨.
*/
class cWeapon //부모 클래스
{
protected://자식 클래스에서 접근이 가능함
    int     m_nAttDamage;       //공격력
    int     m_nDurability;      //내구도
public://어디에서든 가능
    virtual void Attack() {     //공격하기
        cout << "맨손 공격!!" << endl;
    }
    virtual void Defence(){     //방어하기
        cout << "방어하기!!" << endl;
    }
 };

class cSword : public cWeapon
{
public:
    void Attack() override
    {
        cout << "검으로 공격!!" << endl;
    }
    void Defence() override
    {
        cout << "검으로 방어!!" << endl;
    }

};

class cGun : public cWeapon
{
public:
    void Attack() override
    {
        cout << "총으로 공격!!" << endl;
    }
    void Defence() override
    {
        cout << "맨손 방어!!" << endl;
    }

};

int main()
{
    cWeapon* pWeapon = new cWeapon;

    pWeapon->Attack();
    pWeapon->Defence();
    delete pWeapon;

    pWeapon = new cSword;
    pWeapon->Attack();
    pWeapon->Defence();
    delete pWeapon; 
    //선언은 부모 클래스로 하되 생성은 자식 클래스로 한다.

    system("pause");

    return 0;
}