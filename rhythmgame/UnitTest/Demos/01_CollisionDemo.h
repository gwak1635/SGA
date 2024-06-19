#pragma once

#include "Geomatries/Rect.h"

class CollisionDemo : public IObject
{
public:
    // IObject을(를) 통해 상속됨
    void Init() override;
    void Destroy() override;
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;

private:
    Rect* player = nullptr;
    Rect* other = nullptr;
};