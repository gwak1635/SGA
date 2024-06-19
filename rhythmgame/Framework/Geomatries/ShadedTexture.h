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

    // ���α׷��Ӱ� ������ CPU���� GPU�� �Ѱ��� �����͵�
    // 16, 32, 64 ... �� ������ ũ��� ������ָ� ����.
    struct Data
    {
        int selection;          // ȿ�� ���� ��ȣ
        
        int blurCount;          // �� ����
        Vector2 textureSize;    // �̹��� ������
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