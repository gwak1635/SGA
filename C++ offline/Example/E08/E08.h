#pragma once

#include "../Define/GlobalDefine.h"

/*
�Լ��� ���α׷��� ��ü Ȥ�� �Ϻθ� �׷�ȭ ���Ѽ� ���� �и���ų �� �ִ�
����� �ǹ��Ѵ�.

�̷��� ���� �и���Ų �ڵ�� �ʿ��Ҷ� ���� �ҷ��ͼ� ���������� ����ϴ� ����
�����ϴ�.

�츮�� ����ϰ� �ִ� Main���� ������ E00 �ø��� ���� �Լ��� �Ϻ��̴�.

�̷��� �Լ��� ����ϱ� ���ؼ� �Լ��� ���ο��� ����� �����͸� �ǳ��ִ�
�ŰԺ�����, �Լ��� ���ο��� ������ ��ȯ��ų ��ȯ���� �ʿ��ѵ�

���⿡ �������� �ŰԺ����� ��ȯ���� ��Ű�� ������� ������ �߻��Ѵ�.

Ex)
void AFun();        // void == ��ȯ���� ����, () == �Ű� ������ ����
// ��, �ƹ��͵� ��ȯ���� �ʰ� �ƹ��͵� ���� �ʾƵ� �����ϴ� �Լ�

int bFun();         
// int == int�� �����͸� ��ȯ�� �ŰԺ����� ���� �Լ�
float bFun(int aValue) 
// float�� �����͸� ��ȯ�ϸ� int�� �ŰԺ����� �䱸�ϴ�
(�ش� �ŰԺ����� �̸��� �ӽ������� aValue�� ������) �Լ�

�̷��� ������� �Լ��� �����ѵ� ���� ���ǿ� ������� ������ �Լ��� ������
{}�� �Բ� �ۼ��� �Ǵµ�, �̶� ����� ������ ���� ������ �ݵ�� ���� ����
�ʿ�� ����.

�Ϲ������� ��� ���Ͽ��� �Լ����� �������ص� cpp���Ͽ��� �ش� �Լ��� ������
�����Ѵ�.

�̶� �̷��� ������� ������ �ϱ� ���ؼ��� �ݵ�� cpp���� ���ʿ�
��������� ��Ŭ��� ����� �Ѵ�.

�̷������� �پ��� �߰�ȣ�� ����ϴٺ��� �߰�ȣ �ۿ��� ���� ������
�ش� �߰�ȣ �ȿ��� ����Ҽ� ������, �߰�ȣ �ȿ��� ���� ������
�ܺη� ���������� ���� �߻��ϴµ�

�̴� �����Ϸ��� �߰�ȣ�� �������� ������ ������ �����̴�.

���� �ۿ� �ִ� (Ȥ�� �� ������ �ִ�)�����ʹ� ���� ������ ���°���
���������� ���� �ȿ��� ������� �����͵��� ���� ������ ������ ����
�����Ϸ��� �ڵ����� �ش� �����͸� ���������� ������, ���� Ư�� �����͸�
�ܺη� �����ʹٸ� �ܺο� �ش� �����͸� ��Ƶ� ������ ����� �־� �Ұ��̴�.

����, ���� �̸��� ������ ������ �۰� ���ʿ� ����ƴ� �ϴ��� �ش�
���� ���ο����� �ش� ������ �ִ� ������ �켱������ ����ϴ� Ư¡�� �ִ�.

Ex)
int aValue      // aVAlue--�� ������ �޴´�.
{
    int aValue  // aValue++�� ������ �޴´�.
    aValue++;
}
aValue--; 

�Լ��� ���ο��� �ڱ� �ڽ��� �ҷ����� ��� ���� �����ϴµ�,
�̸� ��� �Լ��� �θ���.

��� �Լ��� �� �״�� �ڱ� �ڽ����� ���ư��� �Լ��̸� ������ �ݺ����� ������
Ư¡�� ���ϰ� �ִ�.

��, ��� �Լ��� �Ϲ����� �ݺ������� ���� �� ���̰� ��� �Լ� ����
�ݵ�� ��Ͱ� ���� ���� ��͸� ����� ����ϴ� Ư¡�� �ִ�.

��� �Լ��� ������ ������ �ڵ带 ������ �ݺ��ؾ� �ϸ� �����͸� ����ؼ�
������ ���ϴ� ������ ���ϰ� ����°� ����.

�Լ��� ���� ������ �ŰԺ����� ������ �ƴ� �ش� �ŰԺ����� ������ ����
������ �ִ� ���纻�� ���ο��� ���ȴ�. 
// �� ���ο��� 1���Ѵٰ� ������ 1 �������� �ʴ´�.

�׷��� ������ ����, �Լ� ���ο��� �ŰԺ����� ������ �������� ������
�����ϰ� �ʹٸ� �ش� �������� �ڷ��� �ڿ� &(���۷���)�� �ٿ��ָ� �ȴ�.

&(���۷���)�� �ش� �������� �ּҰ��� ��ȯ�����ִ� ����̰� �ش� �ּҸ�
�ǳ��ָ� �ش� �ּҸ� �����ذ� �����Ͱ� �ش� �ּҿ� �ִ� ���� �������ֱ� ������
������ �����Ͱ� �����ȴ�.

������ ���� ����ϴ� scanf���� &�� �ʿ��� �����̴�.
scanf���� ������ �Լ��̰�, �ش� �Լ����� ���ϴ� ���� �츮�� �־��� ������
�ֱ� ���ؼ��� &�� ���� �ش� ������ ����ִ��� �˷��� �ʿ䰡 �ִ� ���̴�.
*/

void E08();

void Up10Value(int temp1);

void RealUp10Value(int& temp1);

void SumValues(int temp1, int temp2, int& out);

void SumValues(int temp1, int temp2, int& out1, int& out2);