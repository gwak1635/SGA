#include "stdafx.h"
#include "cMainGame.h"
// 메인 게임 클래스 : 전체 게임 클래스를 관리하는 클래스
// 플레이어 클래스
// 스톡 클래스 : 인벤토리 및 상점의 부모 클래스 - 아이템 관리
// 인벤트리 클래스 (스톡) 플레이어가 보유 중인 아이템을 관리하는 클래스
// 상점 클래스 상점의 아이템 관리 클래스, 상점을 구현
// 타운 클래스 : 마을을 구현한 클래스

int main()
{
    system("mode con: cols=96 lines =27");

    cMainGame* pMg = new cMainGame;
    bool isPlaying = true;

    while (isPlaying) {
        pMg->MainPlay();

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//esc키 입력 시
            isPlaying = false;
    }
}
