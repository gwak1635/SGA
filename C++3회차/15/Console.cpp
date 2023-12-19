#include "stdafx.h"


//매개변수가 포인터를 가지고 있다면 주소값을 요구하는 것이다.
int Add(int* a, int* b) {
    *a += 10;
    *b -= 5;

    return *a + *b;
}

/*
포인터란?
주소값을 가리키는(저장하는) 변수
*/

void Suffle(int *arrData) {

    int nSrc;
    int nDest;
    int nTemp;

    for (int i = 0; i < 100; i++)
    {
        nSrc = rand() % 10;
        nDest = rand() % 10;

        nTemp = arrData[nSrc];
        arrData[nSrc] = arrData[nDest];
        arrData[nDest] = nTemp;
    }
}

int main()
{
    srand(time(NULL));
    rand();

    int nA, nB, nC;

    // new 연산을 통해서 메모리에 공간을 할당한다
    // *변수가 그 할당된 메모리 공간을 가리킨다.
    int *pA = new int;
    int *pB = new int;

    *pA = 10;
    *pB = 5;

    cout << pA << ", " << pB << endl;

    nC = Add(pA, pB);

    cout << *pA <<", "<<*pB << endl;
    cout << nC << endl;


    //delete를 쓰지 않으면 메모리 누수가 발생한다
    delete pA;
    delete pB;

    //배열의 이름은 배열의 첫번째 인자의 주솟값을 가르킨다.
    
    int nArray[10];

    for (int i = 0; i < 10; i++)
    {
        nArray[i] = i + 1;
    }
    //narray[0] = *(주솟값+0)
    //narray[1]= *(주솟값+1)[선언 변수의 크기에 따라 달라짐]
    cout << *nArray << endl;
    cout << *(nArray + 1) << endl;

    Suffle(nArray);

    for (int i = 0; i < 10; i++)
    {
        cout << nArray[i] << endl;
    }

    system("pause");

    
    return 0;
}