#pragma once
class GameNode
{
public:
	GameNode();
	~GameNode();

	//�����Լ��� �������̵带 ���� �ʰ� �θ��� �Լ��� ȣ���Ѵ�
	virtual void Init() = 0;//���� ���� �Լ� [�θ𿡼��� �Լ� �������� ����] (�������̵带 �ؾ߸� ��)
	virtual void Update() = 0;
	virtual void Render() = 0;
};

