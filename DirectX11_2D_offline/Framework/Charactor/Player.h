#pragma once

#include "Geomatries/TextureRect.h"

class Player
{
public:
    Player(Vector3 position, Vector3 size);
    ~Player();

    void Update();
    void Render();

    void Move();
    void Jump();

    BoundingBox* GetCollision() { return image->GetCollision(); }

    float GetPositionY() { return position.y; }
    void SetPositionY(float yPos) { this->position.y = yPos; }

    Vector3 GetSize() { return size; }

    void SetImage(wstring path) { image->SetImage(path); }

private:
    TextureRect* image;

    Vector3 position;
    Vector3 size;

    bool moveR = false;

    bool bJump = false;

    float maxJumpT = 0.75f;
    float curJumpT = 0.0f;

    float maxJumpSpd = 20.0f;
    float curJumpSpd = maxJumpSpd;

    bool bFall = false;

    float jumpStartY = 0.0f;
};