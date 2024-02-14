#include<iostream>
#include<string>
using namespace std;

template<typename T> class Character
{
private:
	T name;
public:
	void Set(T name) {
		this->name = name;
	}

	void Print(){
		cout << "캐릭터 이름 : " << name << endl;
	}
};

//상속 시 특수화 필요
class Player : public Character<string>
{

};

class A
{
public:
	void Test() {};//클래스 내부 정의 시 인라인 처리!
	inline void Test2();
	_inline void Test3();
	__inline void Test4();
};

void main() {
	Character<int> ob;
	ob.Set(20);
	ob.Print();

	Player player;
	player.Set("포링");
	player.Print();

}

inline void A::Test2()
{
}
