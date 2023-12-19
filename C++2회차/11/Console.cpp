// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

int main()
{
    int nArray[10];
	int nArray2[10] = { 0, };
	for (int i = 0; i < 10; i++)
	{
		nArray[i] = i + 1;
	}

	int nDArray[10][5] = {
		{1,2,3,4,5},
		{6,7,8,9,10},
		{6,7,8,9,15},
		{6,7,8,9,20},
		{6,7,8,9,10},
		{6,7,8,9,30},
		{6,7,8,9,10},
		{6,7,8,9,40},
		{6,7,8,9,10},
		{6,7,8,9,10},
	};

	int nDArray2[10][5] = { {0,} };
	
	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			nDArray[i][j] = (j + 1) + (i * 5);
		}
	}*/

	/*for (int i = 0; i < 50; i++)
		nDArray[i / 5][i % 5] = i+1 ;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << nDArray[i][j] << ", ";
		}
	}*/

	char szStar[5][5];

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i + j <= 4) {
				szStar[i][j] = '*';
			}
			else {
				szStar[i][j] = '-';
			}
		
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << szStar[i][j];
		}
		cout << endl;
	}

	system("pause");
	return 0;
}
