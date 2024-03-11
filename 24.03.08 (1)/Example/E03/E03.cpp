#include "E03.h"

void E03()
{
    int aValue = 0;
    int bValue = 0;

    printf("숫자 2개를 입력해 주세요 : ");
    scanf("%d %d", &aValue, &bValue);

    // 산술연산자는 기본적인 사칙연산같은 수학적 계산을 하는 연산자를 말한다.
    printf("\n=== 산술 연산자 ===\n");
    printf("%d + %d = %d\n", aValue, bValue, aValue + bValue);
    printf("%d * %d = %d\n", aValue, bValue, aValue * bValue);
    printf("%d %% %d = %d\n", aValue, bValue, aValue % bValue);

    // 비교연산자는 좌항과 우항이 같은지 다른지 누가더 큰지 같은 계산을 통해
    // 참과 거짓을 반환하는 연산자를 말하며,
    // 컴퓨터에게 0은 거짓이고 0이 아닌 모든수는 참이기 때문에
    // 참일경우 1을 거짓일 경우 0을 반환한다.
    printf("\n=== 비교 연산자 ===\n");
    printf("%d == %d = %d\n", aValue, bValue, aValue == bValue);    // 같다
    printf("%d > %d = %d\n", aValue, bValue, aValue > bValue);      // 크다
    printf("%d <= %d = %d\n", aValue, bValue, aValue <= bValue);    // 작거나 같다
    printf("%d != %d = %d\n", aValue, bValue, aValue != bValue);    // 다르다

    // | 기호는 \를 시프트와 함께 누르면 나온다.
    // 논리연산자는 &&(AND), ||(OR), !(NOT)으로 이루어져 있으며
    // AND는 두개의 데이터가 전부 참일경우(0이 아닐경우) 참을 반환하고,
    // OR는 둘중 하나 이상의 데이더가 참일경우 참을 반환하고,
    // NOT은 참일경우 거짓을 거짓일 경우 참을 즉, 0일경우 1을 0이 아닐경우 0을
    // 반환한다.
    printf("\n=== 논리 연산자 ===\n");
    printf("%d && %d = %d\n", aValue, bValue, aValue && bValue);    // AND
    printf("%d || %d = %d\n", aValue, bValue, aValue || bValue);    // OR
    printf("!%d = %d\n", aValue, !aValue);                          // NOT

    // 증감연산은 해당 변수의 1을 더하거나 빼는 연산자이다.
    // 단, 증감연산은 해당 변수 앞, 뒤에 붙일수 있는데 붙이는 위치에 따라
    // 연산되는 방식이 달라진다.
    
    // 앞에 붙이는경우 전위 증감 연산이라 부르고 해당 변수가 선언되어있는
    // 기능을 실행하기전에 해당 변수의 값을 변화시킨뒤 기능을 실행하고
    
    // 뒤에 붙이는경우 후위 증감 연산이라 부르고 해당 변순가 선언되어있는
    // 기능을 실행한 후에 해당 변수의 값을 변화시킨다.
    printf("\n=== 증감 연산자 ===\n");
    printf("++%d, --%d\n", ++aValue, --bValue); // 증감 후 출력
    printf("%d++, %d--\n", aValue++, bValue--); // 출력 후 증감
    printf("증감 연산 후 : %d, %d\n", aValue, bValue);

    // 할당 연산자는 좌항에다 우항의 값을 연산하거나 바로 넣는 연산자를 말하며,
     
    // = 만 있는 단순 할당 연산자는 좌항에다가 우항의값을 덮어 씌우겠다 라는
    // 의미를 지녔고 == (같다)와 햇갈리지 않게 주의하자

    // 다른 연산자와 =이 있는 복잡 할당 연산자는 (Ex, +=, -=, *=, /= ...)
    // 원본의 값에 해당 연산을 실행한뒤 덮어씌우겠다는 의미를 지니고
    // A += B 는 A = A + B 로 해석할수 있다.
    printf("\n=== 할당 연산자 ===\n");
    printf("%d -= 2 = ", aValue);
    printf("%d\n", aValue -= 2);
    printf("%d += 2 = ", bValue);
    printf("%d\n", bValue += 2);

    // 비트 연산자는 피 연산자를 비트단위로 변환시켜(0과 1로 변환시켜)
    // 자릿수와 0과 1을 변환하는 연산자들을 말한다.
    printf("\n=== 비트 연산자 ===\n");
    // &는 두개의 피 연산자의 비트값의 자릿수가 모두 1인 값을 반환
    // Ex 9 & 5 일경우 9 = 1001 , 5 = 0101 이기 때문에
    // 0001 즉, 1이 반환된다.
    printf("%d & %d = %d\n", aValue, bValue, aValue & bValue);
    // |는 두개의 피 연산자의 비트값의 자릿수가 하나라도 1인 값을 반환
    // Ex 9 & 5 일경우 9 = 1001 , 5 = 0101 이기 때문에
    // 1101 즉, 13이 반환된다.
    printf("%d | %d = %d\n", aValue, bValue, aValue | bValue);
    // ^는 두개의 피 연산자의 비트값의 자릿수가 하나만 1인 값을 반환
    // Ex 9 & 5 일경우 9 = 1001 , 5 = 0101 이기 때문에
    // 1100 즉, 12가 반환된다.
    printf("%d ^ %d = %d\n", aValue, bValue, aValue ^ bValue);
    // ~는 피 연산자의 비트값중 0은 1로 1은 0으로 반환
    // Ex 9 의경우 1001 이 0110으로 즉, 6이 반환된다.
    // ~의 경우 실제 인트값의 비트는 0000 4자리가 아니라 0000 0000 0000 0000의
    // 16자리(32비트 기준)이기 때문에 1001이 반전되는게 아닌
    // 0000 0000 0000 1001이 반전되어 1111 1111 1111 0110으로 값이 나와
    // 예상한 값과는 차이가 있다.
    printf("~%d = %d\n", aValue, ~aValue);
    // << 와 >> 는 지정한 수만큼 해당 피연산자 비트단위를 해당 방향으로
    // 이동시켜랴 라는 의미를 지니고 빈칸엔 0을 집어넣는다.
    // 단, 이때 초과된 값이나 미만인 값은 지운다.
    // Ex 9 << 2의 경우 1001이 오른쪽으로 2칸 비트칸을 이동하고
    // 남은 공간에 0을 집어넣으면 100100이 되기 때문에 값은 36
    // Ex 9 >> 2의 경우 1001이 왼쪽으로 2칸 비트칸 이동하고
    // 0의 자릿수 밑으로 떨어진 값은 지우기 때문에 0010 즉, 2가 된다.
    printf("%d << 2 = %d\n", aValue, aValue << 2);
    printf("%d >> 2 = %d\n", aValue, aValue >> 2);

    // 조건 연산자는 ?와 :의 한 세트이며,
    // ?의 앞에있는 조건이 참일경우 : 의 앞에있는 데이터를
    // 거짓이라면 : 의 뒤에있는 데이터를 반환한다.
    // Ex, (9 < 5)는 거짓이기 때문에 ? 9 : 5 라는 코드가 있다면 : 뒤에있는
    // 5가 반환된다.
    printf("\n=== 조건 연산자 ===\n");
    printf("(%d < %d) ? %d : %d = %d\n", aValue, bValue, aValue, bValue,
        (aValue < bValue) ? aValue : bValue);

    /*
    과제! 큰수 찾아 연속 비교하기

    조건1. 초기에 2개의 숫자를 입력받아 둘중 큰수 찾기

    조건2. 큰수를 찾았다면 추가로 1개의 숫자를 입력받아 해당 수와 다시 비교하기
    조건2_1. 이 과정을 총 5번 반복하기

    Ex) 예시, 이렇게 똑같이 안해도 됨
    숫자 두개를 입력해 주세요 : 5 9
    둘중 큰 숫자는 9입니다.
    다시 숫자를 입력해주세요 : 8
    둘중 큰 숫자는 9입니다.
    다시 숫자를 입력해주세요 : 10
    둘중 큰 숫자는 10입니다.
    .
    .
    .

    추가 조건 // 위의 코드를 완성했을경우 추가로 도전 해볼만한 조건, 안해도됨
    추가1. 변수 최대한 적게만들기
    추가2. 최소값도 기록하기
    추가3. 숫자 3개 입력받아 비교하기

    과제 제출 방식은 코드 결과 스크린샷 + 프로젝트 파일 이며,
    
    파일을 올릴때 해당 폴더를 압축하기전에 폴더 안에있는 
    .vs(안보이면 숨김항목 표시 키면됨)와 x64(Example폴더 내부에도 있을수도 있음)
    를 지우고 압축하면 용량이 엄청엄청 줄어듬

    실패했으면 실패한 스크릿샷 + 파일 이라도 올리기

    제출 기간은 24.01.26 까지 // 다음 수업 시작 전까지
    */
}
