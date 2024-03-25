#pragma once

#include "../Define/GlobalDefine.h"

/*
C�� C++�� �ٺ������� �ڵ����� ���̴� �������� ������,
�� ���� �����°��� �ڵ带 ���� ��İ� ���α׷����� ������ ��ȭ����.

������ C�� �ʿ��� ��ɵ��� ���������� �ϳ��� ������
�Ʒ��� ��� �̾����� ����� [������ ���α׷���]�� ����� �԰�

C++�� C�� �޸� �ʿ��� ����� �� ���ο� '��ü'��� ���� �����
�ش� ��ü���� ���� ��ȣ�ۿ��� �ϸ� ���α׷����� ���������
[��ü ������ ���α׷���]�� ����ϴ� ���̴�.

��ü�� ���α׷��ֿ��� ���� �ϳ��� �������� �����ϸ�,
������ ��ü�� �ڽ��� �ؾߵǴ� �ϰ� ���� ���ƾ��ϴ� ���� �����ؾ� �ϰ�
��ü���� ���� �����ϰų� �ٸ� ��ü�� �����Կ� �־ �մ�� ������ ������
�־�� �Ұ��̴�.

�׷��⶧���� C++�� ��ü������ ���α׷��Ӱ� �ڵ��� ���� �����ϱ� ����
�������� ������ �ƴ� ������ �ڵ��� ��ƴ��� �� ������ ����������
������� �е������� �������� ����̱� ������ ���ݱ��� ���ǰ� �ִ�.

Ư�� ���Ӱ��� ������ ��ü�� �����ϰ� �ش� ��ü���� ���� �ڽŵ��� ����
�ൿ�� ��ȣ�ۿ��� �ϴ� ���α׷��̶�� ������ ��ü���� ���α׷����� ����Ҽ�
�ۿ� ����.

������ ���÷� �÷��̾�� ���Ͱ� ������ �ϴ� ���α׷��� �ִٰ� ������

������ ����ϴ� C�� ������ ����̸� ���α׷� ���� �����ٰ� �������
���Ϳ� �÷��̾��� ���ݵ��� �Է��صе� �� �Ʒ��� ���ǹ��� �ݺ������
������ ���ϰ� ���� �ϴ½����� ������ ����� �ְ�
���� ������ �پ��� ��Ȳ���� �ݺ��ȴٸ� �ش� ��ɵ��� �Լ��� ���
����Ҽ��� �������̴�.

�̷��� ���α׷��� C++�� ��ü���� ���α׷������� �ٲ۴ٸ�
�켱 �÷��̾��� ���ݰ� �����ϴ� ����� �������ִ� ��ü��
������ ���ݰ� �����ϴ� ���, �״±�ɰ��� ���Ͱ� �� �ൿ�� ������ �ִ�
��ü�� ������ �Ұ��̸�,
�ش� ��ü���� �����Ŀ� ������ ��ü�� ���� ���α׷����� �����ͼ�
�÷��̾�� ���Ͱ� �� �ൿ�� ���� ��������� �Ѵ�.
�׸��� ���� ����ó�� ���۰� ���� �ִٸ� �ش� ���۰� ���� �����
��Ī �Ŵ����� �θ��� �ý��� ��ü�� ����� �ش� �Ŵ����� �÷��̾ �����ϰ�
���͸� �����ϰ� ������ �������� ��Ű�� �� �پ��� ���ҵ� ����� �Ұ��̴�.
*/

/*
c++���� ���� �����ѰͰ� ���� ��ü�� �����ϱ� ���� class ��� ���ο�
�ڷ����� ����� �´�.

class�� �⺻������ �Լ��� ���� ���� ������ ������, �ش� Ŭ������ ����
��ü�� �����Ѵ�.

class�� 4���� Ư¡�� ���������� �����ѵ�,
�⺻������ ���ʿ��� �����͸� �ܺο� ����� �߻�ȭ,
Ư�� Ŭ�������� �θ� �ڽİ��踦 ����� �θ��� �ڵ带 �ڽĿ��� �����ִ� ���,
���� �̸��� ��ü�� �پ��� ������� ������ְ� �ϴ� ������,
�ܺο��� �����ϴ°��� �����ϰ� �����͸� ��ȣ,�����ϴ� ĸ��ȭ�� �����Ѵ�.

���⼭ �߻�ȭ�� ĸ��ȭ�� �ٺ������� ū ���̰� ���⶧���� 3���� Ư¡�̶���� �Ѵ�.

�켱������ �˾ƺ����� Ŭ������ ���� �����Ϳ����� ��ȣ�� �����̴�.

Ŭ������ �⺻������ �ڽ� ���ο� ����� �پ��� �Լ��� ������ Ư���� ��ȣ �����
�ο��ϴµ� ��ȣ ��޿� ���� �ش� �����͸� ����Ҽ��ִ� ����� �����ȴ�.

public�� ��ΰ� �����Ҽ� �ִ�. ��� ��ȣ ����̸� Ŭ������ ����, �ܺο���
�ش� �����͸� ���� ����Ҽ��ִ�.

protected�� �ڽŰ� ������ �����Ҽ� �ִ�. ��� ��ȣ ����̸�, Ŭ������ ���ο�
�ش� Ŭ������ ��ӹ޴� �ڽ��� �ش� �����͵��� ����� �� �ִ�.

���������� private ����� �ڱ� �ڽŸ� ����� �� �ִ� �����Ͷ�� ���̰�
private������� ��ȣ�޴� �����͵��� ��� ��쿡���� �ܺο��� ������ �� ����.

���� Ŭ������ �⺻������ �ƹ��� ��ȣ����� �������� �ʾ����� �ڽ��� ������
�����͵��� private������� ��ȣ�Ѵ�.

�׷��⿡ ���� �ڱ� �ڽŸ��� �ٸ� �ܺο��� �ش� �����͵��� ����ϰ� ���ְ� ������
�ݵ�� �ʿ信���� public�̳� protected�� ������� �Ѵ�.

�׸��� ���α׷����� �ϴٺ��� private������� ��ȣ�ް��ִ� �����͵��� �����ϰų�
�����;��ϴ� ��찡 �߻��ϱ� ���, �̶� public�� �ش� �����͸� �����ϰų�
�������� �Լ��� ����� ����ϰ� �Ϲ����̸�

�������� �Լ��� Getter, �����ϴ� �Լ��� Setter �� �θ���.
*/

// E09��� �̸��� Ŭ������ �������.
class E09
{
// �ڽ��� ���ϴ� ��ȣ��ް� :(�ݷ�)�� ����� �ش� ��ȣ����� �����ٰ� �Ҽ��ִ�.
public: 
    // �⺻ ������ // �ŰԺ����� �ƹ��͵� ���� �ʴ� ������
    E09();
    // ������
    E09(int aValue, int bValue);
    // �Ҹ��� // �տ� ~�� ������ �Ҹ���
    ~E09();
    
    /*
    Ŭ������ ��� ������ û����(���赵,���� ��)�� ������ ���α׷��Ӱ�
    ������ �Լ��� ������ �������մ� ��ü�� ���� ���� �����δ� ��
    �̴ٺ���, �ش� ��ü�� ������ٿ� ������ٴ� ����� �Լ��� �ʿ��ϴ�.

    �̷��� �Լ����� �����ڿ� �Ҹ��ڶ� �θ���, �����ڿ� �Ҹ��ڴ� �ش�
    Ŭ������ �̸��� ������ �̸��� ���� �Լ��� ���������.

    �̶� ��ȯ���� �ʿ����.

    �׸��� �����ڴ� ������ �����ϴ°��� �����ѵ�, �̴� �Լ� �����ε���
    ���� �����̴�. ��, �ŰԺ����� �޶����� �����ڵ� ������ ������ִ�.
    */

    // �⺻���� getter�� setter
    int GetA() { return aValue; }
    void SetA(int value) { aValue = value; }

    // thisŰ����� �ڱ� �ڽ��� ����Ű�� �������̴�.
    // ���Ը��ϸ� �ڽ��� �ּҸ� �˰��ִ� �����Ͷ�� ���� �ȴ�.
    int GetB() { return this->bValue; }
    void SetB(int bValue) { this->bValue = bValue; }

    void ABSum();
    void ABMax();
    void ABMin();

private: // ������ʹ� private ����

    // ������� �ٸ��� ������ ���� public�� �Լ��� �ְ�
    // private�� ������ �ִ´�.

    int aValue = 0;
    int bValue = 0;
};
/*
����! ��ǳ� ģ���� �����

����1. �� �ݺ����� ���ع��� �����̴� �� �����
����1_1. ���� 2�� �迭�� �����. // ũ�� ���� (�ּ� 5x5)
# = ��, @ = �÷��̾�, & = ���ع�, % = ������
����1_2. �� �ݺ������� ���ع��� ���� �������� �̵�(�¿� �� ����)
����1_3. �迭 ���� ������ ���ع��� �ݴ� �������� �̵�

����2. �÷��̾� ����
����2_1. WASD�� �̵�, ���� ������� ����
����2_2. �÷��̾� ü�� ����
����2_3. ���ع��� ������ ü�� ���� + ������������ �̵�
����2_4. �����۰� ������ ü�� ȸ��

����3. �ݴ��� ���� ���޽� ���� �¸� , ü�� 0 ���ϰ� �ɽ� ���� �й�

// ��Ʈ
0. Windows.h ��Ŭ��� �ϱ�

1. sleep �Լ��� ����
1_1. sleep(1000);�̶� �Է��ϸ� �ܼ�â�� 1�ʰ� ����ٰ� �ٽ� ������
1_2. sleep(500); �̶� �Է��ϸ� �ܼ�â�� 0.5�ʰ� ����

2. system("cls"); ��� ġ�� �ܼ�â ����� ����
*/