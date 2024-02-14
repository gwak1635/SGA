#include <iostream>
#include <stdio.h>
using namespace std;

//템플릿 특수화: 함수by자료형?
//템플릿은 인라인 함수같아서 순서에 관계없음!
template<typename T> void Print(T data)
{
	cout << "함수 : " << data << endl;
}

template<typename T> void Print(int data)
{
	printf("특수화 : %d\n", data);
}

template<typename T> void Print(char data)
{
	printf("특수화 : %c\n", data);
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