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
		cout << "ĳ���� �̸� : " << name << endl;
	}
};

//��� �� Ư��ȭ �ʿ�
class Player : public Character<string>
{

};

class A
{
public:
	void Test() {};//Ŭ���� ���� ���� �� �ζ��� ó��!
	inline void Test2();
	_inline void Test3();
	__inline void Test4();
};

void main() {
	Character<int> ob;
	ob.Set(20);
	ob.Print();

	Player player;
	player.Set("����");
	player.Print();

}

inline void A::Test2()
{
}
