#include "stdafx.h"


/*
조건문 if, else if, else

관계연산자 == < > <= >= !=

논리 연산자 &&(AND연산자) ||(OR연산자)

&, |: 비트연산자	
*/

int main()
{
	int nA = 20;
	int nB = 5, nC = 3;

	if (nA < 10 && nA > 5)
		cout << "nA의 값은 10보다 작고 5보다 크다." << endl;
	else
		cout << "nA의 값은 10보다 작다." << endl;


}

/*함수를 만들 줄 아는 에붕이
그렇다면 이런 함수를 만들어 보자
주어진 조건 n개중 n개만 '참'일 경우 true를 리턴하는 함수
*/