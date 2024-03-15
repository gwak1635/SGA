#include "E02.h"

void E02()
{
	// 정수형 
	short sValue = 10;		// 2바이트
	int iValue = 20;		// 4바이트
	long lValue = 30;		// 4바이트
	long long llValue = 40;	// 8바이트

	// 실수형
	float fValue = 3.14f;	// 4바이트
	double dValue = 6.28;	// 8바이트

	// 문자형
	char cValue = 'A';		// 1바이트

	/*
	printf에서 특정 변수가 가지고 있는 데이터를 출력하기 위해서는
	해당 변수에 데이터를 꺼내겠다는 의미를 지닌 서식문자라는것을
	입력해야 한다.

	서식문자들은 %로 시작하는게 대부분이며, 각 자료형마다 정해진
	서식문자가 존재한다.

	정수형은 short과 int는 %d, long은 %ld, long long은 %lld를 사용하며,
	실수형은 float은 %f, double은 %lf를 사용한다.
	문자형 char는 %c를 사용한다.
	*/

	printf("=== 정수형 문자 출력 ===\n");
	printf("Short 문자 : %d\n", sValue);
	printf("Int 문자 : %d\n", iValue);
	printf("Long 문자 : %ld\n", lValue);
	printf("Long Long 문자 : %lld\n", llValue);

	cout << "=== 실수형 문자 출력 ===" << endl;
	cout << "Float 문자 : " << fValue << endl;
	cout << "Double 문자 : " << dValue << endl;

	printf("=== 문자형 출력 ===\n");
	printf("Char 문자 : %c\n", cValue);
	// %c 서식문자로는 한글은 출력할수 없다.
	// 한글은 2Byte짜리 문자인데 char는 1Byte짜리 문자형이기 때문에
	// 한글을 char에 넣을수가 없다.


	int aValue = 0;
	int bValue = 0;

	/*
	프로그램에서 콘솔창을 통해 입력을 받고싶을땐 주로 scanf와 cin을 사용한다.

	scanf 같은경우는 서식문자를 통해 읽어올 데이터의 자료형을 정하고,
	해당 자료형에 맞는 데이터를 뒤에 &(레퍼런스)와 같이 적은 변수에다가
	저장한다. 

	단, scanf는 기본적으로 입력받을 데이터의 최소 크기와 최대 크기가 정해져
	있지않기 때문에 자료형이 받을수 없을정도의 데이터를 입력받아도 억지로
	넣을려고하면서 에러가 발생한다.

	그렇기 때문에 VS 에서는 scanf_s라는 독자적인 기능을 사용하길 원하지만,
	해당 함수는 VS에서만 사용가능한 함수이기 때문에 범용성이 떨어질수 있어

	그냥 scanf를 사용하기 위해서는 #include <stdio.h> 보다 위에
	#define _CRT_SECURE_NO_WARNINGS를 입력해 줘야한다.
	*/

	printf("aValue에 넣을 값을 입력해 주세요! : ");
	scanf("%d", &aValue);

	cout << "bValue에 넣을 값을 입력해 주세요! : ";
	cin >> bValue;

	printf("입력한 데이터! A : %d\n", aValue);
	printf("입력한 데이터! B : %d\n", bValue);

	printf("\n=== 간단한 사칙연산 ===\n");
	printf("A + B = %d\n", aValue + bValue);
	printf("A - B = %d\n", aValue - bValue);
	printf("A * B = %d\n", aValue * bValue);
	printf("A / B = %.3f\n", aValue / (float)bValue);
	printf("A %% B = %d\n", aValue % bValue); // 나머지 연산
	// 좌항에서 우항을 나눴을때 나오는 나머지를 반환

	/*
	정수형과 정수형끼리의 계산은 반드시 정수형 결과값만 나오기 때문에
	만약 정수형과 정수형의 계산에서 실수형 값을 얻어내고 싶다면
	둘중 하나를 일시적으로 실수형으로 바꿔줘야한다.

	이러한 기능을 형변환이라 부른다.

	형변환은 기본적으로 원하는 변수 앞에 ()와 해당 괄호안에 원하는
	자료형을 적는걸로 가능하며, 이런식으로 프로그래머가 작성하는 
	형변환은 명시적 형 변환이라 부르고

	같은 자료형이 아닌 계산에서 컴파일러는 자동으로 가장 값손실이 
	적은 방식으로 둘중 하나의 자료형을 다른 자료형과 동일하게 
	바꿔버리는데, 이런식으로 프로그래머가 작성하지 않는 형변환은
	묵시적 형 변환이라 부른다.
	*/
}
