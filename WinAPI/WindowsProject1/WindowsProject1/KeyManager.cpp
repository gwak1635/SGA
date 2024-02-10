#include "framework.h"
#include "KeyManager.h"

void KeyManager::Setup()
{
    m_bitKeyUp.reset();
    m_bitKeyDown.reset();
}

bool KeyManager::isOnceKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) {
        //키가 이전에 눌리지 않은 상태
        if (!m_bitKeyDown[key]) {
            //눌린 상태로 변환
            m_bitKeyDown.set(key, true);
            return true;
        }
    }
    else {
        m_bitKeyDown.set(key, false);
    }

    return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
    //키가 계속 눌러져 있다면
    if (GetAsyncKeyState(key) & 0x8000) {
         m_bitKeyUp.set(key, true);
    }
    else {
        //키가 눌렀다가 뗐을 때
        if (m_bitKeyUp[key]) {
            m_bitKeyUp.set(key, false);
            return true;
        }
    }
    return false;
}

bool KeyManager::isStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) return true;
    return false;
}

bool KeyManager::isToggleKey(int key)
{
    if (GetAsyncKeyState(key) & 0x0001) return true;
    return false;
}
