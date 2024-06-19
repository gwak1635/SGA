#include "stdafx.h"
#include "01_CollisionDemo.h"

void CollisionDemo::Init()
{
    player = new Rect({ 100,100,0 }, { 100,100,1 });
    other = new Rect({ 300,300,0 }, { 100,100,1 });
}

void CollisionDemo::Destroy()
{
    SAFE_DELETE(other);
    SAFE_DELETE(player);
}

void CollisionDemo::Update()
{
    player->Move();

    if (BoundingBox::AABB(player->GetCollision(), other->GetCollision()) ||
        BoundingBox::OBB(player->GetCollision(), other->GetCollision()))
    {
        other->SetColor(Color(0, 1, 0, 1));
    }
    else
    {
        other->SetColor(Color(0.6f, 0.3f, 0, 1));
    }

    player->Update();
    other->Update();
}

void CollisionDemo::Render()
{
    player->Render();
    other->Render();
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI()
{
    player->GUI();
    other->GUI();
}
