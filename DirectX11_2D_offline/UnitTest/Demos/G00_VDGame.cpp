#include "stdafx.h"
#include "G00_VDGame.h"

void VDGame::Init()
{
    begin = new Rect(
        Vector3(WinMaxWidth * 0.5f - 375, WinMaxHeight * 0.5f, 0),
        Vector3(150, 300, 1), 0.0f);
    begin->SetColor(Color(0.7f, 1, 0.7f, 1));

    end = new Rect(
        Vector3(WinMaxWidth*0.5f+375, WinMaxHeight * 0.5f, 0),
        Vector3(150, 300, 1), 0.0f);
    end->SetColor(Color(0.7f, 1, 0.7f, 1));
    
    floor.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0),
        Vector3(500, 200, 1), 0.0f)
    );
    floor.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f -250, WinMaxHeight * 0.5f -125, 0),
        Vector3(100, 50, 1), 0.0f)
    );
    floor.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 250, WinMaxHeight * 0.5f+125, 0),
        Vector3(100, 50, 1), 0.0f)
    );
    
    int wallduke = 5;

    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f -450, WinMaxHeight * 0.5f, 0),
        Vector3(wallduke, 300+ wallduke, 1), 0.0f)
    );
    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f -300, WinMaxHeight * 0.5f+25, 0),
        Vector3(wallduke, 250+ wallduke, 1), 0.0f)
    );
    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f - 250, WinMaxHeight * 0.5f, 0),
        Vector3(wallduke, 200+ wallduke, 1), 0.0f)
    );
    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f - 200, WinMaxHeight * 0.5f-125, 0),
        Vector3(wallduke, 50+ wallduke, 1), 0.0f)
    );
    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 450, WinMaxHeight * 0.5f, 0),
        Vector3(wallduke, 300 + wallduke, 1), 0.0f)
    );
    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 300, WinMaxHeight * 0.5f - 25, 0),
        Vector3(wallduke, 250 + wallduke, 1), 0.0f)
    );
    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 250, WinMaxHeight * 0.5f, 0),
        Vector3(wallduke, 200 + wallduke, 1), 0.0f)
    );
    Vwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 200, WinMaxHeight * 0.5f + 125, 0),
        Vector3(wallduke, 50 + wallduke, 1), 0.0f)
    );

    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f -375, WinMaxHeight * 0.5f + 150, 0),
        Vector3(wallduke+150, wallduke, 1), 0.0f)
    );
    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 325, WinMaxHeight * 0.5f + 150, 0),
        Vector3(wallduke + 250, wallduke, 1), 0.0f)
    );
    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f -25, WinMaxHeight * 0.5f + 100, 0),
        Vector3(wallduke + 450, wallduke, 1), 0.0f)
    );
    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 275, WinMaxHeight * 0.5f + 100, 0),
        Vector3(wallduke + 50, wallduke, 1), 0.0f)
    );

    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 375, WinMaxHeight * 0.5f - 150, 0),
        Vector3(wallduke + 150, wallduke, 1), 0.0f)
    );
    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f - 325, WinMaxHeight * 0.5f - 150, 0),
        Vector3(wallduke + 250, wallduke, 1), 0.0f)
    );
    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f + 25, WinMaxHeight * 0.5f -100, 0),
        Vector3(wallduke + 450, wallduke, 1), 0.0f)
    );
    Hwall.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f - 275, WinMaxHeight * 0.5f -100, 0),
        Vector3(wallduke + 50, wallduke, 1), 0.0f)
    );

    for (int i = 0; i < 4; i++)
    {
        hazard.push_back(new Rect(
            Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f-75+50*i, 0),
            Vector3(20, 20, 1), 0.0f)
        );
        if (i % 2 == 0)
            hazard[i]->SetGoingLeft(false);
    }

    player = new Rect(
        Vector3(WinMaxWidth * 0.5f - 375, WinMaxHeight * 0.5f, 0),
        Vector3(35, 35, 1), 0.0f);
    player->SetColor(Color(1, 0, 0, 1));
    
    begin->UpdateWorld();
    end->UpdateWorld();
    for (Rect* r : floor)
    {
        r->SetColor(Color(0.9f, 0.9f, 1, 1));
        r->UpdateWorld();
    }
    for (Rect* r : Vwall)
    {
        r->SetColor(Color(0, 0, 0, 1));
        r->UpdateWorld();
    }
    for (Rect* r : Hwall)
    {
        r->SetColor(Color(0, 0, 0, 1));
        r->UpdateWorld();
    }
    for (Rect* r : hazard)
    {
        r->SetColor(Color(0, 0, 1, 1));
        r->UpdateWorld();
    }
    player->UpdateWorld();
}

void VDGame::Destroy()
{
    SAFE_DELETE(player);
    for (Rect* r : hazard)
    {
        SAFE_DELETE(r);
    }
    for (Rect* r : Hwall)
    {
        SAFE_DELETE(r);
    }
    for (Rect* r : Vwall)
    {
        SAFE_DELETE(r);
    }
    for (Rect* r : floor)
    {
        SAFE_DELETE(r);
    }
    SAFE_DELETE(end);
    SAFE_DELETE(begin);
}

void VDGame::Update()
{
    player->Move();
    player->Update();
    if (BoundingBox::AABB(player->GetCollision(), end->GetCollision()))
    {
        end->SetColor(Color(0, 1, 0, 1));
    }
    for (Rect* r : hazard)
    {
        r->AutoMove();
        if (BoundingBox::AABB(player->GetCollision(), r->GetCollision()))
            player->GotoBegin();
    }
    for (Rect* r : hazard)
    {
        r->Update();
    }
    begin->Update();
    end->Update();
    for (Rect* r : floor)
    {
        r->Update();
    }
    for (Rect* r : Vwall)
    {
        r->Update();
        
        if (BoundingBox::AABB(player->GetCollision(), r->GetCollision()))
        {
            player->RevercemoveAD();
        }
    }
    for (Rect* r : Hwall)
    {
        r->Update();

        if (BoundingBox::AABB(player->GetCollision(), r->GetCollision()))
        {
            player->RevercemoveWS();
        }
    }
}

void VDGame::Render()
{    
    begin->Render();
    end->Render();
    for (Rect* r : floor)
    {
        r->Render();
    }
    for (Rect* r : Vwall)
    {
        r->Render();
    }
    for (Rect* r : Hwall)
    {
        r->Render();
    }
    for (Rect* r : hazard)
    {
        r->Render();
    }
    player->Render();

}

void VDGame::PostRender()
{
}

void VDGame::GUI()
{
}
