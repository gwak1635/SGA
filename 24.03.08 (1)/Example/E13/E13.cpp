#include "E13.h"

E13::E13()
{
	vecA.push_back(1);
	vecA.push_back(2);
	vecA.push_back(3);
	vecA.push_back(4);
	vecA.push_back(5);

	// .size(): ������ ���
		/*for (int i = 0; i < vecA.size(); i++)
		{
			printf("%d��° ��� : %d\n", i, vecA[i]);
		}*/

	//���� ��� for��: for(�ڷ��� �����̸�: �̾Ƴ� ����)[��� �����͸� �̾Ƴ�]
	for (int i : vecA) {//1���� n�� ã�ƺ�
		printf("vecA�� ������ �ִ� ��� : %d\n", i);
	}

	printf("\n\n");

	vecA.assign(10,0);//���� �����(Ŭ����) (������ ��, �̰ɷ�), ���� �ʱ�ȭ
	for (int i : vecA) {
		printf("vecA�� ������ �ִ� ��� : %d\n", i);
	}
}

E13::~E13()
{
}
