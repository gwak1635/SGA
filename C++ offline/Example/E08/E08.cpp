#include "E08.h"

// 함수를 헤더에서 선언하고 cpp에서 구현하는게 아닌
// cpp에서 선언과 구현을 전부 할 경우
// 해당 함수가 사용될 위치보다 더 위쪽에 해당 함수가 있어야
// 사용하는 것이 가능하다.
int SumValues(int temp1, int temp2)
{
    // 만약 함수가 반환값을 요구한다면
    // 해당 반환값의 자료형에 맞춰 
    // return으로 반환할 데이터를 건내주면 된다.
    return temp1 + temp2;
}

void E08()
{
    int aValue = 10;
    int bValue = 20;

    // 함수의 매게변수 이름과 넣을 변수의 이름은 관련이 없다.
    printf("aValue + bValue = %d\n",SumValues(aValue, bValue));

    // 반환값은 컴파일러가 연산이나 함수를 실행한후 나온 변형된 데이터를
    // 메모리 상의 공간에 돌려주는것을 의미하는데
    // 이때, 해당 데이터를 다른곳에서 부르거나 사용할수 있다.

    Up10Value(aValue);
    printf("aValue 값 : %d\n", aValue);
    // %p는 해당 데이터의 주소를 알려주는 서식문자로
    // 사용할때 &를 붙인 변수를 건내주면 된다.
    printf("aValue의 주소 : %p\n", &aValue);

    RealUp10Value(aValue);
    printf("aValue 값 : %d\n", aValue);
    printf("aValue의 주소 : %p\n", &aValue);

    int cValue = 0;
    int dValue = 0;
    SumValues(aValue, bValue, cValue);
    printf("aValue + bValue = cValue(%d)\n", cValue);

    SumValues(aValue, bValue, cValue, dValue);
    printf("aValue + bValue = cValue(%d) + cValue = dValue(%d)\n",
        cValue, dValue);
}

void Up10Value(int temp1)
{
    printf("기존의 매게변수 : %d\n", temp1);
    temp1 += 10;
    printf("증감후 매게변수 : %d\n", temp1);
    printf("매게변수 데이터 주소 : %p\n", &temp1);
}

void RealUp10Value(int& temp1)
{
    // 매게변수에 &를 붙여 값을 건내줄 경우
    // 함수 내부에서 일시적으로 사용할 복사본이 아닌
    // 원본의 데이터를 가져와 가공을 하기 때문에
    // 원본의 데이터를 바꾸는것이 가능해진다.
    printf("기존의 매게변수 : %d\n", temp1);
    temp1 += 10;
    printf("증감후 매게변수 : %d\n", temp1);
    printf("매게변수 데이터 주소 : %p\n", &temp1);
}

// C++은 같은 이름의 함수를 다수 만드는것을 허락해준다.
// 단, 조건으로 반환값은 같지만 매게변수만 달라야 하며
// 이때 매게변수가 증가하든, 요구하는 자료형들이 변하든
// 하나라도 차이점이 있다면 같은 이름의 다른 함수를 만드는것이 가능하고
// 이를 함수 오버로딩이라 부른다.
void SumValues(int temp1, int temp2, int& out)
{
    int temp = 0;
    temp = temp1 + temp2;
    out = temp;
}

// 매게변수가 1개 더 생겼으니 함수 오버로딩 조건에 충족한다.
void SumValues(int temp1, int temp2, int& out1, int& out2)
{
    // 이런식으로 다수의 레퍼런스를 이용해 매게변수의 원본값을
    // 수정할수 있다면 2개 이상의 반환값을 만들어 낼 수 도 있다.
    int temp = 0;
    temp = temp1 + temp2;
    out1 = temp;
    temp += out1;
    out2 = temp;
}

/*
과제! 텍스트 게임 틀 만들어기

조건1. 자기가 만들고 싶은 게임 장르 정하기
Ex) RPG, FPS, 미연시, RTS 등등등
// RPG가 가장 쉬울꺼임

조건2. 필요한 기능들 구상해오기
Ex) 전투, 던전 탐색, 마을, 상점
조준점, 탄창, 총
텍스트 출력, 아스키 아트(그림)출력
등등등

조건3. 할수 있는 기능들로 간추리기
// 게임을 만들기 위해 다양한 게임을 찾아보거나
// 좋은하는 게임의 시스템들을 곱씹을수록 해보고 싶어지는데
// 그 게임이 출시가 됐고 잘 팔렸다면 
// 지금당장은 그 게임은 여러분이 못만드는 게임이다.
*/