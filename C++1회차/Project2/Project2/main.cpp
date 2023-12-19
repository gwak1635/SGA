#include <iostream>

using namespace std;

//출력 cout
//입력 cin
//줄바꿈 명령어 endl

/*
10진법, 16진법, 8진법, 2진법
1bit -> 0
*/
void main() {
	// 헝가리안 표기법 :변수명 앞에 데이터 타입 쓰기
	// 변수 선언
	bool isPlaying, bPlay;//b 혹은 is를 소문자로, 뒤에 대문자로
	char chLetter;
	int nAttack;
	short shArmor;
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

	cout << "파워를 입력하세요." << endl;
	cin >> dPower;

	cout << "입력하신 파워는 " << dPower << "입니다." << endl;

	system("pause");

}