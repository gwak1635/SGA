#include "E09.h"

E09::E09()
{
    // �⺻ �����ڰ� ����ɶ� ������ �ڵ�
    // �����Ҷ� �ƹ��͵� �Է����� ������ ����Ǵ� �ڵ�
    aValue = 10;
    bValue = 20;
    printf("�⺻ ������ ȣ��!\n");
}

E09::E09(int aValue, int bValue)
    :aValue(aValue), bValue(bValue)
{
    // ������ �ʱ�ȭ �ϴ� �������
    // �����ڰ� ����Ǳ� ���� :(�ݷ�)�� ����־�
    // ������ ���� �ٲ۵� �����ڸ� ������ �� �� �ִ�.
    printf("�ŰԺ����� �޴� ������ ȣ��!\n");
}

E09::~E09()
{
    // �Ҹ��ڰ������� �ش� ��ü�� ������� ����Ǵ� �Լ���
    // �ַ� �޸𸮸� �Ҵ��ϰ��ִ� �����͸� ��ȯ�ðų�
    // ���̻� ������� ���� �����͸� ����� �ڵ���� ����
    // ������ ���⿡�� ����ų� ��ȯ��ų �����Ͱ� ����.
    printf("�Ҹ��� ȣ��!\n");
}

void E09::ABSum()
{
    printf("aValue + bValue = %d\n", aValue + bValue);
}

void E09::ABMax()
{
    if (aValue > bValue)
    {
        printf("aValue�� ���� �� Ů�ϴ�! %d\n", aValue);
    }
    else if(aValue < bValue)
    {
        printf("bValue�� ���� �� Ů�ϴ�! %d\n", bValue);
    }
    else // ���ٸ�
    {
        printf("aValue�� bValue�� ���� �����ϴ�!\n");
    }
}

void E09::ABMin()
{
    if (aValue > bValue)
    {
        printf("bValue�� ���� �� �۽��ϴ�! %d\n", bValue);
    }
    else if (aValue < bValue)
    {
        printf("aValue�� ���� �� �۽��ϴ�! %d\n", aValue);
    }
    else // ���ٸ�
    {
        printf("aValue�� bValue�� ���� �����ϴ�!\n");
    }
}