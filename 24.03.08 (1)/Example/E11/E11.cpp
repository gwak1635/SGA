#include "E11.h" 

E11::E11()
{
}

E11::~E11()
{
}

void E11::PrintDPtr(int** dPtr)
{
    printf("이중 포인터 출력 : %d\n", **dPtr);
    PrintPtr(*dPtr);
}

void E11::PrintPtr(int* ptr)
{
    printf("포인터가 가지고있는 데이터 출력 : %d\n", *ptr);
}
