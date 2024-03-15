#include "Ex01.h"

#include <random>
// random은 C++에서 랜덤을 더 편하고 쉽게 그리고 안전하게 사용하기 위해 만든
// 기능들 모아놓은 헤더파일이다.

// 만약 다른 파일에서도 사용하고싶다면 글로벌 디파인에 넣어주는게 좋을것이다.
void Ex01()
{
    random_device randD;
    // random_device는 프로그래머가 제어할수없는 난수를 만들어주는 기능이다.

    // uniform_int_distribution은 난수에 따라 뽑아낼 데이터의 자료형과
    // 범위를 지정할수있게 해주는 기능이다.
    uniform_int_distribution<int> intRand(0, 10);

    // 랜덤값을 받을 변수
    int aValue = 0;

    // 이 변수에 = 이 범위에(이 난수를써서);
    aValue = intRand(randD);
    printf("랜덤값 1 출력 : %d\n", aValue);

    // 유니폼과 랜덤디바이스는 매번 실행할때마다 다른 랜던값을 반환한다.
    aValue = intRand(randD);
    printf("랜덤값 2 출력 : %d\n", aValue);
}
