#pragma once
#include "Framework.h"

// WVP
/*
WVP = World, View, Projection
- 3D���� 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ���� �� �ϳ�

1. World // ����
- ���� ������ ���� ��ǥ�迡�� ���� ��ǥ��� ��ȯ�ϴ�
���� �ǹ�
- ���� ��ġ, ȸ�� �� ũ�⸦ ����

2. View // ī�޶�
- ���� ��ǥ�迡�� ī�޶� �ٶ󺸴� ������ ��Ÿ��
- ī�޶��� ��ġ, ���� �� ����

3. Projection // ������
- 3D ������ 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ���� �ǹ�
- �þ߰�, ��ȸ��, ũ���� ��� ���� ����Ͽ� ����
*/

// World�� �����͸� �ǳ��� ����
class WorldBuffer : public ShaderBuffer
{
public:
    WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // ��� �ʱ�ȭ // ��� ���� 0����
        D3DXMatrixIdentity(&data.world);
    }

    void SetWorld(Matrix world)
    {
        // ��� ��ġ // ���� ���� �ٲ�
        D3DXMatrixTranspose(&data.world, &world);
    }

    struct Data
    {
        // CPU���� GPU�� �����͸� �ǳ��� ����
        // 16Byte�̻��� 2��� ���� �־��ִ� ���� ����.
        // Ex) 16, 32, 64 ...
        Matrix world;
    };
private:
    Data data;
};

// View, Proejction
class VPBuffer : public ShaderBuffer
{
public:
    VPBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // ��� �ʱ�ȭ // ��� ���� 0����
        D3DXMatrixIdentity(&data.view);
        D3DXMatrixIdentity(&data.proj);
    }

    void SetView(Matrix view)
    {
        D3DXMatrixTranspose(&data.view, &view);
    }

    void SetProj(Matrix proj)
    {
        D3DXMatrixTranspose(&data.proj, &proj);
    }

    struct Data
    {
        Matrix view;
        Matrix proj;
    };
private:
    Data data;
};