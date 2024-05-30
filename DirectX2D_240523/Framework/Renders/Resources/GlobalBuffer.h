#pragma once

#include "Framework.h"

// GlobalBuffer
// WVP = ����(����) * ��(ī�޶�) * ��������(������)
/*
WVP�� 3D������ ���� 2D ��ũ�� ��ǥ�� ��ȯ�ϴ� ���� �� �ϳ�
����ʹ� ����̱� ������ 3D���ӵ� ��ũ�� ��ǥ�� ��ȯ�ϴ� ������ �ʿ��ϴ�.

World // ����
- ���� ������ �۷ι� ��ǥ�迡�� ���� ��ǥ��� ��ȯ�ϴ� ���� �ǹ��Ѵ�.
- ���� ��ġ, ȸ��, ũ�⸦ �����Ѵ�.

View // ī�޶�
- ī�޶��� ��ġ, ����, �þ߸� ��Ÿ���� ���
- �۷ι� ��ǥ�迡�� ī�޶� �ٶ󺸴� ������ ��Ÿ����. // ���� ī�޶� ��ü�ִ°� X
- ī�޶��� ��ġ�� ������ ��������ش�.

proejction // ������
- 3D������ 2D��ũ�� ��ǥ�� ��ȯ��Ű�� ���
- �þ߰�, ��Ⱦ��, ũ���� ���(�ܸ鵵 ���)���� ����Ͽ� ����
*/

// WorldBuffer
class WorldBuffer : public ShaderBuffer
{
public:

    WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // ��� �ʱ�ȭ
        // �ش� ��� �����Ͱ� ���� 0�� ��
        D3DXMatrixIdentity(&data.world);
    }

    void SetWorld(Matrix world)
    {
        // ��ġ ���
        // ���� ���� ���� ��ȯ 
        // world�� ���� ������ ����.��, world�� ���� ������.������ ��
        D3DXMatrixTranspose(&data.world, &world);
    }

    // CPU�� �ѱ� �����͵��� ����
    // �޸� �Ҵ緮�� ���� 16�� ����� ũ�⸦ �Ҵ��� �ִ°��� ����
    // Ex) int(4Byte) 4�� / char(1Byte) 32��
    struct Data
    {
        // float�� 4�� �ִ� ����ü
        Matrix world;
    };
private:
    Data data;
};


// VPBuffer
class VPBuffer : public ShaderBuffer
{
public:

    VPBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        D3DXMatrixIdentity(&data.view);
        D3DXMatrixIdentity(&data.projection);
    }

    void SetView(Matrix view)
    {
        D3DXMatrixTranspose(&data.view, &view);
    }

    void SetProj(Matrix projection)
    {
        D3DXMatrixTranspose(&data.projection, &projection);
    }

    struct Data
    {
        Matrix view;        // ī�޶�
        Matrix projection;  // ������
    };
private:
    Data data;
};
