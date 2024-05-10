#include "stdafx.h"
#include "G01_TGame.h";

void Tgame::Init()
{
    player = new Rect(
        Vector3(100, 100, 0),
        Vector3(50, 50, 1), 0.0f);
    player->SetColor(Color(1, 0, 0, 1));

    enemy = new Rect(
        Vector3(WinMaxWidth - 100, WinMaxHeight - 100, 0),
        Vector3(50, 50, 1), 0.0f);
    enemy->SetColor(Color(0, 0, 1, 1));
}

void Tgame::Destroy()
{
    SAFE_DELETE(enemy);
    SAFE_DELETE(player);
}

void Tgame::Update()
{
    player->Move();
    enemy->TraceMove(enemy->GetPosition(),player->GetPosition());
    player->Update();
    enemy->Update();

    if (BoundingBox::AABB(player->GetCollision(), enemy->GetCollision())) {
        int x = WinMaxWidth / 2;
        int y = WinMaxHeight / 2;
        while (abs(x - enemy->GetPosition().x) < 100 || abs(y - enemy->GetPosition().y) < 100) {
            x = Random::GetRandomInt(50, WinMaxWidth - 50);
            y = Random::GetRandomInt(50, WinMaxHeight - 50);
        }
        player->SetPosition(Vector3(x,y, 0));
    }
}

void Tgame::Render()
{
    player->Render();
    enemy->Render();
}

void Tgame::PostRender()
{
}

void Tgame::GUI()
{
}
