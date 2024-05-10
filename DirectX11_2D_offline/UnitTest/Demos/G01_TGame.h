#pragma once

#include "Geometries/Rect.h"
#include "Utilities/Random.h"

class Tgame : public IObject {
public:
	// IObject��(��) ���� ��ӵ�
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

private:
	Rect* player = nullptr;
	Rect* enemy = nullptr;
};

/*
����! �߰��ϴ� AI ����� ����
//�Ⱓ: ���� �� �ݿ���(5.3����)

�⺻
:	�÷��̾��� ��ġ�� �˰� �ش� ��ġ�� �̵��ϴ� AI��Ʈ
//�����̵��� �ƴ϶� �÷��̾�ó�� õõ�� �̵��ؾ� ��
//����� ����

�⺻+
: �÷��̾�� ai��Ʈ�� �浹�� �÷��̾�� ������ ��ġ�� �̵�
�� �� ������ ��ġ�� �̵��� ���� ai ��Ʈ�� ����� ��!


�߰�
: �÷��̾ ��ð� AI ��Ʈ�� �浹���� ���� �� �߰� AI��Ʈ ����
//�÷��̾ �÷��̾ ai��Ʈ�� �浹�� �� �浹�� ai��Ʈ�� �����ϰ� ���� ������� ��
// �׸��� �ð��� ������ ��Ÿ��

�����ϸ� ���� ����
// FSM(���� ���� �ӽ�)//AI �˰���
// State Mation//���� ��ȭ ������ ���� // enum ���

*/