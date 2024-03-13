#include "E13.h"

E13::E13()
{
	vecA.push_back(1);
	vecA.push_back(2);
	vecA.push_back(3);
	vecA.push_back(4);
	vecA.push_back(5);

	// .size(): 벡터의 요소
		/*for (int i = 0; i < vecA.size(); i++)
		{
			printf("%d번째 요소 : %d\n", i, vecA[i]);
		}*/

	//범위 기반 for문: for(자료형 변수이름: 뽑아낼 변수)[모든 데이터를 뽑아냄]
	for (int i : vecA) {//1부터 n개 찾아봄
		printf("vecA가 가지고 있는 요소 : %d\n", i);
	}

	printf("\n\n");

	vecA.assign(10,0);//원문 지우기(클리어) (공간의 수, 이걸로), 유사 초기화
	for (int i : vecA) {
		printf("vecA가 가지고 있는 요소 : %d\n", i);
	}
}

E13::~E13()
{
}
