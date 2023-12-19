// Sangsok.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

//가상함수는 자식 클래스에서 재정의 가능. 재정의가 안 되면

class cWeapon
{
private://상속되지 않음.
    
protected://상속되나 외부에서 접근 가능
    int m_nAttDamage;
    int m_nDurability;

public://어디에서든 접근 가능
    virtual void Attack() //공격 - 가상함수
    {
        cout << "맨손 공격!!" << endl;
    }
    virtual void Defence()
    {
        cout << "방어 하기!!" << endl;
    }
};

class cSword : public cWeapon
{
public:
    void Attack() override
    {
        cout << "칼로 공격!!" << endl;
    }
    void Defence() override
    {
        cout << "칼로 방어!!" << endl;
    }
};

int main()
{
    cSword sword;

    sword.Attack();

    system("pause");

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
