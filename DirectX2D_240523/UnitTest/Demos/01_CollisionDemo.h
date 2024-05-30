#pragma once

#include "Geomatries/Rect.h"

class CollisionDemo : public IObject
{
public:
    // IObject��(��) ���� ��ӵ�
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