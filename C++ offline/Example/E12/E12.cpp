#include "E12.h"

E12::E12()
{
}

E12::~E12()
{
}

Animal::Animal()
{
	aValue = 10;
	bValue = 20;

	printf("Animal 생성!\n");
}

Animal::~Animal()
{
	printf("Animal 소멸!\n");
}

void Animal::PrintAValue()
{
	printf("Animal AVaule 출력! : %d\n", aValue);
}

void Animal::PrintBValue()
{
	printf("Animal BVaule 출력! : %d\n", bValue);
}

Cat::Cat()
{
	aValue = 30;
	bValue = 40;
	printf("Cat 생성!\n");
}

Cat::~Cat()
{
	printf("Cat 소멸!\n");

}

void Cat::PrintAValue()
{
	printf("Cat AVaule 출력! : %d\n", aValue);
}

void Cat::PrintBValue()
{
	printf("Cat BVaule 출력! : %d\n", bValue);
}
