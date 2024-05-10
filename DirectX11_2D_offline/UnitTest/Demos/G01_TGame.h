#pragma once

#include "Geometries/Rect.h"
#include "Utilities/Random.h"

class Tgame : public IObject {
public:
	// IObject을(를) 통해 상속됨
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
과제! 추격하는 AI 만들어 오기
//기간: 다음 주 금요일(5.3까지)

기본
:	플레이어의 위치를 알고 해당 위치로 이동하는 AI렉트
//순간이동이 아니라 플레이어처럼 천천히 이동해야 됨
//방식은 자유

기본+
: 플레이어와 ai렉트와 충돌시 플레이어는 랜덤한 위치로 이동
이 때 랜덤한 위치로 이동한 곳에 ai 렉트가 없어야 함!


추가
: 플레이어가 장시간 AI 렉트가 충돌하지 않을 시 추가 AI렉트 투입
//플레이어가 플레이어가 ai렉트와 충돌할 시 충돌한 ai렉트를 제외하곤 전부 사라져야 함
// 그리고 시간이 지나면 나타남

참고하면 좋을 내용
// FSM(유한 상태 머신)//AI 알고리즘
// State Mation//상태 변화 디자인 패턴 // enum 사용

*/