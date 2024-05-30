#pragma once

#include "Geomatries/Rect.h"

class TGame : public IObject
{
public:
    // IObject��(��) ���� ��ӵ�
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;

};

/*
����! �߰��ϴ� AI����� ����
// �Ⱓ : 24.04.26 ~ 24.05.03

�⺻
: �÷��̾��� ��ġ�� �˰� �ش� ��ġ�� �̵��ϴ� AI ��Ʈ
// �����̵��� �ƴ϶� �÷��̾�ó�� õõ�� �̵��ؾߵ�
// ����� ����

�⺻+
: �÷��̾�� AI ��Ʈ�� �浹�� 
�÷��̾�� ������ ��ġ�� �̵�
// �̶� ������ ��ġ�� �̵��� ���� AI ��Ʈ�� ������ �ִ�
// ������ �����ϱ�
// AI ��Ʈ ��ġ�� ���� �̵� ��ǥ���� ���ܵž� �Ҳ���

�߰�
: �÷��̾ ��ð� AI ��Ʈ�� �浹���� ������
�߰� AI ��Ʈ ����
// �߰� AI ��Ʈ�� ���� �� ���� �÷��̾ AI ��Ʈ��
// �浹�ҽ� �浹�� AI ��Ʈ�� �����ϰ� ���� ���������
// �׸��� �ٽ� �ð��� ������ ��Ÿ��

�����ϸ� ��������
// FSM (���� ���� �ӽ�) // AI �˰���
// State Mation // ���� ��ȭ ������ ���� // enum ���

*/