#include "stdafx.h"
#include "H0_JumpDemo.h"

void JumpDemo::Init()
{
    player = new Player({ 100,100,0 }, { 100,100,1 });
    player->Update();

    floor = new Rect({ WinMaxWidth * 0.5f, 50,0 }, { WinMaxWidth, 100, 1 }, 0.0f);
    floor->Update();

    for (int i = 0; i < 10; i++)
    {
        enemys.push_back(new Rect({ WinMaxWidth + (float)(i * 1000), 150, 0}, {100,200,1}));
        enemys[i]->Update();
    }
}

void JumpDemo::Destroy()
{
    SAFE_DELETE(player);
    SAFE_DELETE(floor);

    for (Rect* r : enemys)
    {
        SAFE_DELETE(r);
    }
}

void JumpDemo::Update()
{
    if (BoundingBox::AABB(player->GetCollision(), floor->GetCollision()))
    {
        float tempY = 0.0f;

        tempY += player->GetSize().y * 0.5f;
        tempY += floor->GetSize().y;

        player->SetPositionY(tempY);
    }

    for (Rect* r : enemys)
    {
        r->SetPosition(r->GetPosition() + Vector3((-300 * Time::Delta()), 0, 0));
        if (BoundingBox::AABB(player->GetCollision(), r->GetCollision()) && pHit == false)
        {
            pHit = true;
        }
    }

    if (t >= 0.5f)
    {
        pHit = false;
        t = 0.0f;
    }

    if (pHit)
    {
        player->SetImage(TexturePath + L"Sample2.jpg");
        t += Time::Delta();
    }
    else
    {
        player->SetImage(TexturePath + L"Sample.jpg");
    }

    player->Update();
    floor->Update();

    for (Rect* r : enemys)
    {
        r->Update();
    }
}

void JumpDemo::Render()
{
    player->Render();
    floor->Render();

    for (Rect* r : enemys)
    {
        r->Render();
    }
}

void JumpDemo::PostRender()
{
}

void JumpDemo::GUI()
{
}
