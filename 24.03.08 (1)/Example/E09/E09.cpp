#include "E09.h"

E09::E09()
{
    // 기본 생성자가 실행될때 진행할 코드
    // 생성할때 아무것도 입력하지 않으면 진행되는 코드
    aValue = 10;
    bValue = 20;
    printf("기본 생성자 호출!\n");
}

E09::E09(int aValue, int bValue)
    :aValue(aValue), bValue(bValue)
{
    // 변수를 초기화 하는 방법으로
    // 생성자가 실행되기 전에 :(콜론)을 집어넣어
    // 변수의 값을 바꾼뒤 생성자를 실행할 수 도 있다.
    printf("매게변수를 받는 생성자 호출!\n");
}

E09::~E09()
{
    // 소멸자같은경우는 해당 객체가 사라질때 실행되는 함수로
    // 주로 메모리를 할당하고있는 데이터를 반환시거나
    // 더이상 사용하지 않을 데이터를 지우는 코드들이 들어가며
    // 당장은 여기에서 지우거나 반환시킬 데이터가 없다.
    printf("소멸자 호출!\n");
}

void E09::ABSum()
{
    printf("aValue + bValue = %d\n", aValue + bValue);
}

void E09::ABMax()
{
    if (aValue > bValue)
    {
        printf("aValue의 값이 더 큽니다! %d\n", aValue);
    }
    else if(aValue < bValue)
    {
        printf("bValue의 값이 더 큽니다! %d\n", bValue);
    }
    else // 같다면
    {
        printf("aValue와 bValue의 값이 같습니다!\n");
    }
}

void E09::ABMin()
{
    if (aValue > bValue)
    {
        printf("bValue의 값이 더 작습니다! %d\n", bValue);
    }
    else if (aValue < bValue)
    {
        printf("aValue의 값이 더 작습니다! %d\n", aValue);
    }
    else // 같다면
    {
        printf("aValue와 bValue의 값이 같습니다!\n");
    }
}