#pragma once

#include "Geomatries/TextureRect.h"

class ShadedBuffer : public ShaderBuffer
{
public:
    ShadedBuffer()
        : ShaderBuffer(&data, sizeof(data))
    {
        data.selection = 1;

        data.blurCount = 1;
        data.textureSize = Vector2(0, 0);
    }

    int* GetSelectionPtr() { return &data.selection; }
    int* GetBlurCountPtr() { return &data.blurCount; }

    void SetTextureSize(Vector2 size)
    {
        data.textureSize = size;
    }

    // 프로그래머가 조작해 CPU에서 GPU로 넘겨줄 데이터들
    // 16, 32, 64 ... 의 데이터 크기로 만들어주면 좋다.
    struct Data
    {
        int selection;          // 효과 지정 번호
        
        int blurCount;          // 블러 강도
        Vector2 textureSize;    // 이미지 사이즈
    };
private:
    Data data;
};

class ShadedTexture : public TextureRect
{
public:
    ShadedTexture(Vector3 position, Vector3 size,
        float rotation, wstring path);
    ~ShadedTexture();

    void Update();
    void Render();
    void GUI();

private:
    ShadedBuffer* sb = nullptr;
};