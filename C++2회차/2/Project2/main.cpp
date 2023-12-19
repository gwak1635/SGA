#include<iostream>

using namespace std;

/*
데이터 자료형
bool	: 1바이트 문자형 - 참과 거짓을 표현(0: 거짓, 1: 참)
char	: 1바이트 문자형 - 문자 하나를 표현 ex) a, b, c
short	: 2바이트 정수형 - (음수, 0, 양수)
int		: 4바이트 정수형
float	: 4바이트 실수형
double	: 8바이트 실수형
*/

/*
연산자
대입 연산자 =
비교 연산자 == (수학에서의 10)
수학에서의 A = 10의 의미는 A는 10과 같다
프로그래밍에서의 A = 10은 A에 10을 대입한다

산술 연산자 + - * / %
*/
void main()
{
	//헝가리안 표기법 : 변수명 앞에 자료형을 표기해 주는 방식

	// 변수 선언
	bool isPlaying, bPlay;
	char chLetter;
	short shArmor;
	int nAttack;
	float fSpeed;
	double dPower;

	isPlaying = true;
	bPlay = false;

	chLetter = 'a';
	shArmor = 10;
	nAttack = 20;
	fSpeed = 3.0f;
	dPower = 4.0;


	cout << chLetter << endl;
	cout << nAttack << endl;
	cout << fSpeed << endl;

	cout << "파워를 입력하세요" << endl;
	cin >> dPower;

	cout << "입력하신 파워는 " << dPower << "입니다." << endl;

	system("pause");
}