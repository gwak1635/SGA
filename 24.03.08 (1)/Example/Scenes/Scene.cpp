#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::e09()
{
	// E09는 클래스이다보니 이전처럼 함수를 불러오는게 아닌
	// 클래스 객체를 만들어 생성자를 호출해 줘야한다.
	// E09 scene; 
	// 아무것도 적지 않으면 기본 생성자가 호출

	E09 scene = E09(40, 50);
	// 매게변수를 받을경우 이렇게 만들어 주면 된다.

	// 만든 클래스에 .(접근 지정자)를 입력해 해당 클래스가
	// public에 둔 함수나 변수에 접근할 수 있다.
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

	printf("구조체에 넣을 데이터를 입력해 주세요 (3개) : ");
	scanf("%d %d %d", &temp1, &temp2, &temp3);

	E10 ee = E10(temp1, temp2, temp3);

	printf("기본 데이터 호출!\n");
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
		printf("기본값은 IntValue 입니다!\n");
		break;
	case FLOAT_VALUE:
		printf("FloatValue 입니다!\n");
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
	// int*에 int형 변수의 주소를 넣었음
	e11.SetAPTr(&aValue);

	printf("E11이 가지고있는 int* : %d\n", 
		*(e11.GetAValuePtr()));

	int* bValue = &aValue;
	int** cValue = &bValue;

	// bValue는 aValue의 주소를 가지고있고
	// 역참조 bValue를 20으로 넣어주면 aValue가
	// 가지고있는 값이 20이 된다.
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