#pragma once
#include "SingletonBase.h"
#include <bitset>

using namespace std;

/*
bitset : bool Ÿ���� ��� �ִ� �ڷ� ����(�����̳�)
set() : bit ��� 1�� ����
set(i, value) : i��° ���� value�� ����
reset() : bit ��� 0���� ����
[] : �迭 ������ ������ ���� ex) bit[10] = false;
flip() : bit �� ��� ��ȯ 

all() : ��� ��Ʈ�� 1�� �� TRUE ��ȯ
none() : ��� ��Ʈ�� 0�� �� true ��ȯ
any() : 1���� 1�̸� true ��ȯ
count() : ���� 1�� ���õ� ��Ʈ�� ���� ��ȯ
*/

#define g_pKeyManager KeyManager::GetInstance()

#define KEYMAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEYMAX> m_bitKeyUp;
	bitset<KEYMAX> m_bitKeyDown;

public:
	void Setup(); // Ű�Ŵ��� �ʱ�ȭ
	bool isOnceKeyDown(int key); //Ű�� �� �� ����
	bool isOnceKeyUp(int key); //Ű�� ������ ��
	bool isStayKeyDown(int key); //Ű�� ������ ����
	bool isToggleKey(int key); //��� Ű(Ű�� �Ѱ� ��[Num Lock ���� ����])

};

