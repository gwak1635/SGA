#include <iostream>

using namespace std;

/* ������ �ڷ���
bool : 1����Ʈ ������(1��Ʈ �ƴ�!) - ���� ������ ǥ�� true(1), false(0)
char : 1����Ʈ ������ - ������ �ϳ��� ǥ��

short : 2����Ʈ ������ (����,0,���)
int : 4����Ʈ ������ - ������ ǥ��
float : 4����Ʈ �Ǽ���(�Ҽ��� ǥ��)
double : 8����Ʈ �Ǽ���
*/

/* ������
���� ������ = 
�� ������ ==(���п����� =)
���� A = 10�� �ǹ̴� A�� 10�� ����
���α׷��ֿ��� A=10�� �ǹ̴� A�� 10�� �����Ѵ�.

��� ������+ - *  /

*/

void main() {

	//�밡���� ǥ���
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
	dPower = 4.0;//�ڿ� l���̸� �մ����̷���~

	cout << chLetter << endl;
	cout << nAtt << endl;
	cout << fSpeed << endl;

	cout << "�Ŀ��� �Է��ϼ���." << endl;
	cin >> dPower;

	cout << "�Ŀ�: " << dPower << "�� �Էµ�." << endl;

	system("pause");
}