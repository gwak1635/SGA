#include "E05.h"

void E05()
{
    int aValue = 0;
    int bValue = 0;

    printf("�ݺ��� Ƚ���� �Է��� �ּ��� : ");
    scanf("%d", &bValue);

    // �⺻���� for�� ����
    for (int i = 0; i < bValue; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    
    // �⺻���� for�� ���°� �ƴϴ��� �ʱ���, ������, �ݺ����� �ִٸ�
    // for�� ����ȴ�.
    // �ʱ����� ���� for�� ����ɶ� �ѹ� ����Ǵ� �κп� �Ұ��ϰ�
    // �������� 0�̳� 0�� �ƴϳĸ� Ȯ���ϴ� �κ��̸�
    // �ݺ����� �ٽ� ������ Ȯ������ ����� �κ��� ���̴�.
    for (aValue += 10; !aValue && bValue; aValue = bValue)
    {

    }
    aValue = 0;

    // aValue�� bValue�� �۴ٸ� ����ؼ� �ݺ�
    while (aValue < bValue)
    {
        // while���� ����Ҷ� �ݵ�� ���ο��� ������ ���ټ� �ִ� �ڵ尡 �ʿ��ϴ�.
        aValue++;
        printf("%d ", aValue);
    }
    printf("\n");
    
    aValue = 0;
    while (aValue < bValue)
    {
        // 2�� �������� �������� 1�ΰ�� == Ȧ��
        if (aValue % 2 == 1)
        {
            printf("%d ", aValue);
        }

        aValue++;
    }
    printf("\n");

    aValue = 0;
    while (aValue < bValue) // ¦���϶� �ǳʶٴ� �ڵ� 
    {
        // 2�� �������� �������� 0�ΰ�� == ¦��
        if (aValue % 2 == 0)
        {
            // ��Ƽ�� Ű����� ���̻� �Ʒ��� ������ �������� �ʰ�
            // ���� �ڵ��� �帧���� �̵���Ű�� Ű����
            // �ݺ����̶�� �ݺ����� �ƴ϶�� �׳� ���� �ڵ���ġ��
            aValue++;   // aValue�� �����ϴ°͵� ��ŵ�ϴ� �߰��� �Է�
            continue;
        }
        printf("%d ", aValue);
        aValue++;
    }
    printf("\n");

    aValue = 0;
    while (aValue < bValue) // 5������ ����Ѵ�
    {
        printf("%d ", aValue);
        if (aValue == 5)
        {
            // �ݺ������� break�� ����Ұ��
            // �ش� �ݺ����� ������ ������ ������ ����� ���ش�.
            // ���Ը��� ���̻� �ݺ����� ������ ����ϴ°� �ƴ�
            // ���� �׸��ΰ� �����ٴ� �̾߱��.
            break;
        }
        aValue++;
    }
    printf("\n");

    aValue = 0;
    do // while(aValue > bValue)
    {
        printf("Do ~ While�� �ݵ�� �ѹ��� �����Ѵ�!\n");
    } while (aValue > bValue); // �⺻������ aValue�� 0�̹Ƿ� Ŭ���� ����
    // do ~ while�� �ѹ� ������ ������ �����̶�� ���̻� �������� �ʴ´�.
}

/*
����! ���� �ùķ��̼� �����

����1. �÷��̾�, ������ ���� �����
����1_1. �⺻ ������ ü��, ���ݷ�, ����

����2. �÷��̾�� ���ʹ� ������ ü���� 0�� �ɶ����� ����
����2_1. �������� ���ݷ� - �������� ���
����2_1. ���� ������ �� ũ�ٸ� 0���� ���

����3. ������ ü���� 0�̵Ǿ� ������ ������ ���ڰ� �������� ����ϱ�
����3_1. ����� ���(�÷��̾�� ���Ͱ� �Ѵ� �׾������) �÷��̾��� �¸��� ����

=== ������� ���̵� : ��

�߰� ����1. �÷��̾�� ������ ������ �Է��ؼ� �ޱ�
�߰� ����1_1. �Է¹��� ������ �״�� �÷��̾�� ������ ���ݿ� ����ֱ�

�߰� ����2. �÷��̾�� ������ ���� ���� ����ϱ� 
�߰� ����2_1. ����,��� �� ���� ��Ȳ ����϶�� ��

�߰� ����3. ������ �ִ� 3ȸ �����Ͽ�, 2ȸ �¸��� ��� ǥ���ϱ�
�߰� ����3_1. ������ �ٽ� ���۵ɶ� �й��� ����� ü���� ȸ��, ���ڴ� ����
�߰� ����3_2. ���� �½� ���� ������ ���� 2ȸ �¸��� 3��° ������ ���� ����
// 3�� 2��

=== ������� ���̵� : ��

�ϵ� ����1. �÷��̾�� ������ ���ݿ� ȸ��, ġ��Ÿ Ȯ��, ġ��Ÿ ���� �߰��ϱ�
�ϵ� ����1_1. ȸ�� ������ Ȯ���� ���� �ǰݽ� �������� ���� ���� // Miss ��
�ϵ� ����1_2. ġ��Ÿ Ȯ�� ���ݿ� ���� ���ݽ� �������� ġ��Ÿ ������ŭ �߰��ϱ�

�ϵ� ����2. ��Ȳ ��� ���� �߰��ϱ�
�ϵ� ����2_1. ȸ�ǿ� ġ��Ÿ�� ��Ȳ������ �˷��ֱ�
�ϵ� ����2_2. ���� ���� ü�°� �׿��� ���ݵ鵵 ����ϱ�

=== ������� ���̵� : ��

���� : 2024_01_31 �ϱ��� // ���� ���� ���۶�����
*/