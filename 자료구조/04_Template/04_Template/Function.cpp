#include <iostream>
#include <stdio.h>
using namespace std;

//���ø� Ư��ȭ: �Լ�by�ڷ���?
//���ø��� �ζ��� �Լ����Ƽ� ������ �������!
template<typename T> void Print(T data)
{
	cout << "�Լ� : " << data << endl;
}

template<typename T> void Print(int data)
{
	printf("Ư��ȭ : %d\n", data);
}

template<typename T> void Print(char data)
{
	printf("Ư��ȭ : %c\n", data);
}

void main() {
	int i = 10;
	Print<int>(i);

	char b = 'A';
	Print<char>(b);

	float t = 20.0f;
	Print<float>(t);

	double td = 20.0L;
	Print<int>(td);
}