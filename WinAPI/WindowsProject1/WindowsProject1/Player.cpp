#include "framework.h"
#include "Player.h"

void Player::Init()
{
	m_ptPos1 = { WINSIZEX / 2, WINSIZEY - 30 };							// 조작할 렉트의 좌표 값
	m_fMoveSpeed = 20;
}

void Player::Update()
{
    // 키입력 처리
   // 삼항식 (조건) ? 참일 때 : 거짓일 때
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)//0x0001:누른 순간에만 단 한 번 작동함
    {
        m_ptPos1.x -= (m_rtBox1.left >= m_fMoveSpeed) ? m_fMoveSpeed : 0;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
        m_ptPos1.x += (m_rtBox1.right <= WINSIZEX - m_fMoveSpeed) ? m_fMoveSpeed : 0;
    }


    // 포지션 위치에 따른 렉트 정보 업데이트
    m_rtBox1 = RECT_MAKE(m_ptPos1.x, m_ptPos1.y, 50);


}

void Player::Render()
{
    RECT_DRAW(m_rtBox1);
}
