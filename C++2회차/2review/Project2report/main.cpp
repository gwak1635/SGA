#include<iostream>

using namespace std;

int main() {

	int nA;
	int nB;

	cout << "정수 A값을 입력하세요 : ";
	cin >> nA;
	cout << "정수 B값을 입력하세요 : ";
	cin >> nB;
	
	cout << "A:" << nA << ", B:" << nB << endl;

	cout << "A+B = " << nA + nB << endl;
	cout << "A-B = " << nA - nB << endl;
	cout << "A*B = " << nA * nB << endl;
	cout << "A/B = " << nA / nB << endl;

	system("pause");
	return 0;
}