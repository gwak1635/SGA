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

	printf("Animal ����!\n");
}

Animal::~Animal()
{
	printf("Animal �Ҹ�!\n");
}

void Animal::PrintAValue()
{
	printf("Animal AVaule ���! : %d\n", aValue);
}

void Animal::PrintBValue()
{
	printf("Animal BVaule ���! : %d\n", bValue);
}

Cat::Cat()
{
	aValue = 30;
	bValue = 40;
	printf("Cat ����!\n");
}

Cat::~Cat()
{
	printf("Cat �Ҹ�!\n");

}

void Cat::PrintAValue()
{
	printf("Cat AVaule ���! : %d\n", aValue);
}

void Cat::PrintBValue()
{
	printf("Cat BVaule ���! : %d\n", bValue);
}
