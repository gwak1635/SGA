#include "Ex01.h"

#include <random>
// random�� C++���� ������ �� ���ϰ� ���� �׸��� �����ϰ� ����ϱ� ���� ����
// ��ɵ� ��Ƴ��� ��������̴�.

// ���� �ٸ� ���Ͽ����� ����ϰ�ʹٸ� �۷ι� �����ο� �־��ִ°� �������̴�.
void Ex01()
{
    random_device randD;
    // random_device�� ���α׷��Ӱ� �����Ҽ����� ������ ������ִ� ����̴�.

    // uniform_int_distribution�� ������ ���� �̾Ƴ� �������� �ڷ�����
    // ������ �����Ҽ��ְ� ���ִ� ����̴�.
    uniform_int_distribution<int> intRand(0, 10);

    // �������� ���� ����
    int aValue = 0;

    // �� ������ = �� ������(�� �������Ἥ);
    aValue = intRand(randD);
    printf("������ 1 ��� : %d\n", aValue);

    // �������� ��������̽��� �Ź� �����Ҷ����� �ٸ� �������� ��ȯ�Ѵ�.
    aValue = intRand(randD);
    printf("������ 2 ��� : %d\n", aValue);
}
