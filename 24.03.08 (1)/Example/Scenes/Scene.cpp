#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::e09()
{
	// E09�� Ŭ�����̴ٺ��� ����ó�� �Լ��� �ҷ����°� �ƴ�
	// Ŭ���� ��ü�� ����� �����ڸ� ȣ���� ����Ѵ�.
	// E09 scene; 
	// �ƹ��͵� ���� ������ �⺻ �����ڰ� ȣ��

	E09 scene = E09(40, 50);
	// �ŰԺ����� ������� �̷��� ����� �ָ� �ȴ�.

	// ���� Ŭ������ .(���� ������)�� �Է��� �ش� Ŭ������
	// public�� �� �Լ��� ������ ������ �� �ִ�.
	scene.ABMax();

	scene.SetA(scene.GetB() + 10);
	scene.ABMax();

	int temp = 0;
	scanf("%d", &temp);
	scene.SetB(temp);

	scene.ABSum();
}

void Scene::e10()
{
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;

	printf("����ü�� ���� �����͸� �Է��� �ּ��� (3��) : ");
	scanf("%d %d %d", &temp1, &temp2, &temp3);

	E10 ee = E10(temp1, temp2, temp3);

	printf("�⺻ ������ ȣ��!\n");
	printf("aValue = %d\n", ee.GetInfo().aValue);
	printf("bValue = %d\n", ee.GetInfo().bValue);
	printf("cValue = %d\n", ee.GetInfo().cValue);

	switch (temp1)
	{
	case 1:
		ee.SetValueType(INT_VALUE);
		break;
	case 2:
		ee.SetValueType(FLOAT_VALUE);
		break;
	}

	switch (ee.GetValueType())
	{
	case INT_VALUE:
		printf("�⺻���� IntValue �Դϴ�!\n");
		break;
	case FLOAT_VALUE:
		printf("FloatValue �Դϴ�!\n");
		break;
	case CHAR_VALUE:
		break;
	case MAX_VALUE:
		break;
	case MAX_PLUS_VALUE:
		break;
	default:
		break;
	}
}

void Scene::e11()
{
	E11 e11 = E11();

	int aValue = 10;
	// int*�� int�� ������ �ּҸ� �־���
	e11.SetAPTr(&aValue);

	printf("E11�� �������ִ� int* : %d\n", 
		*(e11.GetAValuePtr()));

	int* bValue = &aValue;
	int** cValue = &bValue;

	// bValue�� aValue�� �ּҸ� �������ְ�
	// ������ bValue�� 20���� �־��ָ� aValue��
	// �������ִ� ���� 20�� �ȴ�.
	*bValue = 20;

	e11.PrintDPtr(cValue);
}

void Scene::e12()
{
	Animal* anim = new Animal();
	Cat* cat = new Cat();

	anim->PrintAValue();
	anim->PrintBValue();

	cat->PrintAValue();
	cat->PrintBValue();

	Animal* animC = new Cat();

	animC->PrintAValue();
	animC->PrintBValue();

	delete animC;
	delete cat;
	delete anim;
}

void Scene::e13()
{
	E13* e13 = new E13();

	


	delete e13;
	e13 = nullptr;
}