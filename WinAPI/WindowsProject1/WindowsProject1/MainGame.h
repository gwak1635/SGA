#pragma once
#include "GameNode.h"
class MainGame : public GameNode
{

public:

	virtual void Init()   override;
	virtual void Update() override;
	virtual void Render() override;

};