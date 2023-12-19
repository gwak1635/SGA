#include <iostream>

using namespace std;

/* 데이터 자료형
bool : 1바이트 문자형(1비트 아님!) - 참과 거짓을 표현 true(1), false(0)
char : 1바이트 문자형 - 영숫자 하나를 표현

short : 2바이트 정수형 (음수,0,양수)
int : 4바이트 숫자형 - 정수를 표현
float : 4바이트 실수형(소숫점 표현)
double : 8바이트 실수형
*/

/* 연산자
대입 연산자 = 
비교 연산자 ==(수학에서의 =)
수학 A = 10의 의미는 A는 10과 같다
프로그래밍에서 A=10의 의미는 A에 10을 대입한다.

산술 연산자+ - *  /

*/

void main() {

	//헝가리안 표기법
	bool isPlaying, bPlay;
	char chLetter;
	short shArmor;
	int nAtt;
	float fSpeed;
	double dPower;

	isPlaying = true;
	bPlay = false;

	chLetter = 'a';
	shArmor = 10;
	nAtt = 16383;
	fSpeed = 3.0f;
	dPower = 4.0;//뒤에 l붙이면 롱더블이래요~

	cout << chLetter << endl;
	cout << nAtt << endl;
	cout << fSpeed << endl;

	cout << "파워를 입력하세요." << endl;
	cin >> dPower;

	cout << "파워: " << dPower << "로 입력됨." << endl;

	system("pause");
}