#pragma once
class GameNode
{
public:
	GameNode();
	~GameNode();

	//가상함수는 오버라이드를 하지 않고 부모의 함수를 호출한다
	virtual void Init() = 0;//순수 가상 함수 [부모에서는 함수 구현하지 않음] (오버라이드를 해야만 함)
	virtual void Update() = 0;
	virtual void Render() = 0;
};

