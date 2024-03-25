#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size)
    : position(position), size(size)
{
    image = new TextureRect(position, size,0.0f);
    image->SetImage(TexturePath + L"Sample.jpg");
    image->UpdateWorld();
}

Player::~Player()
{
    SAFE_DELETE(image);
}

void Player::Update()
{
    Move();

    image->SetPosition(position);
    image->SetSize(size);
    
    image->Update();
}

void Player::Render()
{
    image->Render();
}

void Player::Move()
{
    if (bJump)
        Jump();

    float mSpd = 100;

    if (Keyboard::Get()->Press('A'))
    {
        position.x -= mSpd * Time::Delta();
        if (Keyboard::Get()->Press('D') && !moveR)
        {
            position.x += (mSpd * 2) * Time::Delta();
        }
    }
    else if (Keyboard::Get()->Press('D'))
    {
        moveR = true;
        position.x += mSpd * Time::Delta();
    }

    if (Keyboard::Get()->Up('D')) moveR = false;

    if (Keyboard::Get()->Down(VK_SPACE) && bJump == false)
    {
        jumpStartY = position.y;
        bJump = true;
    }    
}

void Player::Jump()
{
    // »ó½Â
    if (bFall == false)
    {
        if (curJumpT >= maxJumpT)
        {
            curJumpT = 0.0f;

            bFall = true;
        }
        else
        {
            curJumpSpd -= 10.0f * Time::Delta();

            position.y += curJumpSpd;

            curJumpT += Time::Delta();
        }
    }
    else // ÇÏ°­
    {
        if (curJumpT >= maxJumpT)
        {
            curJumpSpd = maxJumpSpd;

            curJumpT = 0.0f;

            position.y = jumpStartY;

            bJump = false;
            bFall = false;
        }
        else
        {
            curJumpSpd += 10.0f * Time::Delta();

            position.y -= curJumpSpd;

            curJumpT += Time::Delta();
        }
    }
}
