#pragma once
#include "GameNode.h"

struct tagBox
{
	RECT    rt;
	float   speed;
};

class Objects : public GameNode
{
private:
	vector<tagBox>	m_vecBox;   //떨어지는 렉트들의 정보
	int				m_nDelay;

	int				m_nLevel;

public:
	virtual void Init()   override;
	virtual void Update() override;
	virtual void Render() override;
	void SetLevel(int n) { m_nLevel = n; }
	vector<tagBox>& GetBox() { return m_vecBox; }// 대량의 정보는 주솟값(참조자)로 넘긴다! [단, 원본이 변경됨에 주의]
};

