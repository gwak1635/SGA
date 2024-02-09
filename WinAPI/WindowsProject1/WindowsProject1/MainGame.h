#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Objects.h"
class MainGame : public GameNode
{
private:

	int             m_nScore;
	int             m_nLevel;
	
	Player* m_pPlayer;
	Objects* m_pObjects;

public:
	MainGame();
	~MainGame();

	//순수 가상 함수는 자식 함수에서 정의를 강제할 때!
	virtual void Init()   override;
	virtual void Update() override;
	virtual void Render() override;

};