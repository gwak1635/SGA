#pragma once

#include "Geomatries/ShadedTexture.h"
#include "Geomatries/AlphaTexture.h"

class ShadedDemo : public IObject
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
    ShadedTexture* st = nullptr;
    AlphaTexture* at = nullptr;
};