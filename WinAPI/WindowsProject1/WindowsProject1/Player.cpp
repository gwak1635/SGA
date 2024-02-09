#include "framework.h"
#include "Player.h"

void Player::Init()
{
	m_ptPos1 = { WINSIZEX / 2, WINSIZEY - 30 };							// ������ ��Ʈ�� ��ǥ ��
	m_fMoveSpeed = 20;
}

void Player::Update()
{
    // Ű�Է� ó��
   // ���׽� (����) ? ���� �� : ������ ��
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)//0x0001:���� �������� �� �� �� �۵���
    {
        m_ptPos1.x -= (m_rtBox1.left >= m_fMoveSpeed) ? m_fMoveSpeed : 0;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
        m_ptPos1.x += (m_rtBox1.right <= WINSIZEX - m_fMoveSpeed) ? m_fMoveSpeed : 0;
    }


    // ������ ��ġ�� ���� ��Ʈ ���� ������Ʈ
    m_rtBox1 = RECT_MAKE(m_ptPos1.x, m_ptPos1.y, 50);


}

void Player::Render()
{
    RECT_DRAW(m_rtBox1);
}
