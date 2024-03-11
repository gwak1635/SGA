#include "E04.h"

/*
if ~ else같은경우는 괄호안에 들어가는 값이 참인지 거짓인지만 확인하기 때문에
다양한 조건과 복잡한 조건을 넣어도 무리 없이 작동하며,
참인 조건이 나올때까지 해당 조건문을 계속해서 탐색하기에 속도가 느린편이고,
참인 조건의 내용을 실행하고 나면 자동으로 조건문 밖으로 나오는 기능이다.

switch : case의 경우 괄호안에는 반드시 정수형 값이 들어가야 하기 때문에
복잡하거나 다양한 조건을 넣을순 없지만,
해당 값과 같은 값이 선언된 case로 바로 이동하기 때문에 속도가 빠른편이고,
해당 위치로 이동했다 하더라도 이동만하고 어디까지 해야하는지는 모르기 때문에
만약 해당 위치의 기능만 하고 끝내고 싶다면 break 키워드를 입력해 줘야한다.
*/

void E04()
{
    int aValue = 0;
    int bValue = 0;

    // 공백 문자, 널 문자
    // \0은 문자의 0과 같은 초기값으로 사용하는 문자이다. ' ' <- 이렇게 나옴
    char op = '\0';

    printf("사칙연산 수식을 입력해 주세요! : ");
    scanf("%d %c %d", &aValue, &op, &bValue);

    printf("\n=== if ~ else로 만들었을 경우 ===\n");

    // 만약에 op 가 '+'와 같다면
    if (op == '+')
    {
        printf("%d + %d = %d 입니다!\n", aValue, bValue, aValue + bValue);
    }
    // else는 위 내용이 거짓일경우 이고 그뒤에 if를 붙이면
    // 거짓인 상태에서 새로운 조건을 가지고 비교해 참인지 확인한다.
    else if (op == '-')
    {
        printf("%d - %d = %d 입니다!\n", aValue, bValue, aValue - bValue);
    }
    else if (op == '*')
    {
        printf("%d * %d = %d 입니다!\n", aValue, bValue, aValue * bValue);
    }
    else if (op == '/')
    {
        printf("%d / %d = %d 입니다!\n", aValue, bValue, aValue / bValue);
    }
    else // 위에있는 모든 조건이 거짓이라면 // 반드시 참이다.
    {
        printf("잘못된 수식을 입력하셨습니다.\n");
    }

    printf("\n=== switch : case로 만들었을 경우 ===\n");

    switch (op)
    {
    case '+':
    {
        // 여기는 op가 +일때 이동할 위치
        printf("%d + %d = %d\n", aValue, bValue, aValue + bValue);
    }break; 
    // break 키워드는 해당 조건문을 더이상 실행하지 않고 끝내겠다는 의미를 지닌다.
    case '-':
    {
        printf("%d - %d = %d\n", aValue, bValue, aValue - bValue);
    }break;
    case '*':
    {
        printf("%d * %d = %d\n", aValue, bValue, aValue * bValue);
    }break;
    case '/':
    {
        printf("%d / %d = %d\n", aValue, bValue, aValue / bValue);
    }break;
    default :
    {
        // 위에 그 어떠한것도 같은게 없을경우
        printf("잘못된 수식을 입력했습니다.\n");
    }break;
    }
}

/*
과제1! ABCD 4번 출력하기 : 난이도 하

조건1. F5를 눌러 실행했을때 ABCD가 총 4번 출력되야한다.
Ex)
ABCD
ABCD
ABCD
ABCD

조건2. ABCD를 출력하는 코드는 전부 달라야한다.
조건2_1. 다른 변수를 쓰더라도 같은 형태의 코드라면 인정하지 않음
Ex) 
printf("%c%c%c%c",a,b,c,d,);
printf("%c%c%c%c",e,g,f,h,);        // 이거 인정안함

조건3. 반드시 하나의 코드는 한줄의 ABCD만 출력해야한다.

조건4. printf와 cout중 하나만 사용하기

힌트 : 창의력

과제2! 학점 출력하기 : 난이도 중

조건1. 0부터 100까지의 학점을 입력받아 해당 학점에 맞는 등급 표시하기
조건1_1. 90~100점은 A, 80~89는 B, 70~79는 C, 60~69는 D, 59이하는 F

조건2. 해당 숫자의 뒷자리에 따라 상세 등급 표시하기
조건2_1. 0 ~ 3 이면 - , 4 ~ 6 표시안함 , 7 ~ 9 +
Ex) 학점을 입력하세요 : 87
해당 점수의 학점은 B+ 입니다.

조건3. 100점은 A++로 출력한다.

과제3! 가위바위보 만들기 : 난이도 하

조건1. 플레이어는 1. 가위, 2.바위, 3.보자기 중 한가지를 선택한다.

조건2. 랜덤하게 나온 숫자와 플레이어가 입력한 숫자를 비교하여 승,패,무승부 확인

조건3. 총 5회 실행하며, 플레이어의 승패 기록하기
조건3_1. 5회 반복이 끝났다면 승패 기록 출력하기
*/
