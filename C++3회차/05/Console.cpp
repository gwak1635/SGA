#include "stdafx.h"

//반복문
//for, while
//for : 특정 횟수를 반복하도록 만드는 구문
//while : 특정 조건이 성립되는 동안 무한반복하는 구문
//break : 반복문을 강제로 빠져나가게 하는 명령어

int main()
{
	srand(time(NULL));
	rand();

	int nP, nC;
	bool isContinue = true;
	int nPW = 0, nCW = 0;

	//가위바위보 2승 시 종료하는 게임.
	while (isContinue)
	{
		cout << "1.가위 2.바위 3.보 ";
		cin >> nP;

		nC = rand() % 3 + 1;

		if (nP == 1)
		{
			cout << "플레이어 - 가위 vs ";
			if (nC == 1)
			{
				cout << "가위 - 컴퓨터 : 무승부" << endl;
			}
			else if (nC == 2) {
				cout << "바위 - 컴퓨터 : 컴퓨터 승" << endl;
				nCW++;
			}
			else
			{
				cout << "보 - 컴퓨터 : 플레이어 승" << endl;
				nPW++;
			}
		}
		else if (nP == 2) {
			cout << "플레이어 - 바위 vs ";
			if (nC == 1)
			{
				cout << "가위 - 컴퓨터 : 플레이어 승" << endl;
				nPW++;
			}
			else if (nC == 2) {
				cout << "바위 - 컴퓨터 : 무승부" << endl;
			}
			else
			{
				cout << "보 - 컴퓨터 : 컴퓨터 승" << endl;
				nCW++;
			}
		}
		else
		{
			cout << "플레이어 - 보 vs ";
			if (nC == 1)
			{
				cout << "가위 - 컴퓨터 : 컴퓨터 승" << endl;
			}
			else if (nC == 2) {
				cout << "바위 - 컴퓨터 : 플레이어 승" << endl;
				nPW++;
			}
			else
			{
				cout << "보 - 컴퓨터 : 무승부" << endl;
				nCW++;
			}
		}
		
		if (nPW >= 2) {
			cout << "플레이어 최종 승리!" << endl;
			isContinue = false;
		}
		else if (nCW >= 2) {
			cout << "컴퓨터 최종 승리!" << endl;
			isContinue = false; 
		}

	}

	//for (int i = 0; i < 5; i++) {
	//	//1. 변수 선언 및 초기화
	//	//2. 조건 검사 (조건이 맞지 않으면 조건을 빠져나간다)
	//	//3. 알고리즘 실행
	//	//4. 증감값 적용
	//	//5. 2~4번 반복


	//	cout << " : ";
	//	cin >> nA;
	//	cout << " : ";
	//	cin >> nB;

	//	cout << "덧셈 결과 : " << nA + nB << endl;

	//}

	//while (isContinue) {
	//	//1. 조건 검사
	//	//2. 알고리즘 실행

	//	cout << " : ";
	//	cin >> nA;
	//	cout << " : ";
	//	cin >> nB;

	//	cout << "덧셈 결과 : " << nA + nB << endl;
	//	cout << "0.종료, 1.계속 : ";//0과 1 이외의 값은 에러가 나는구나!
	//	cin >> isContinue;

	//}


	system("pause");

	return 0;
}
