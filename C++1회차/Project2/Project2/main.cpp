#include <iostream>

using namespace std;

//��� cout
//�Է� cin
//�ٹٲ� ��ɾ� endl

/*
10����, 16����, 8����, 2����
1bit -> 0
*/
void main() {
	// �밡���� ǥ��� :������ �տ� ������ Ÿ�� ����
	// ���� ����
	bool isPlaying, bPlay;//b Ȥ�� is�� �ҹ��ڷ�, �ڿ� �빮�ڷ�
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

	cout << "�Ŀ��� �Է��ϼ���." << endl;
	cin >> dPower;

	cout << "�Է��Ͻ� �Ŀ��� " << dPower << "�Դϴ�." << endl;

	system("pause");

}