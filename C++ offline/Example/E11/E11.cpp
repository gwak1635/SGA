#include "E11.h" 

E11::E11()
{
}

E11::~E11()
{
}

void E11::PrintDPtr(int** dPtr)
{
    printf("���� ������ ��� : %d\n", **dPtr);
    PrintPtr(*dPtr);
}

void E11::PrintPtr(int* ptr)
{
    printf("�����Ͱ� �������ִ� ������ ��� : %d\n", *ptr);
}
