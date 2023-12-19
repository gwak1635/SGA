#pragma once
class GameNode
{
public:
	GameNode();
	~GameNode();

	virtual void Init() = 0;//순수 가상 함수(부모클래스에는 필요없지만, 가상함수에서는 꼭 필요함)
	virtual void Update() = 0;
	virtual void Render() = 0;
};

