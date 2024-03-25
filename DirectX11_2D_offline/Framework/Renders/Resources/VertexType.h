#pragma once

// �ܻ��� �׸�
struct VertexColor
{
    VertexColor()
        : position(0, 0, 0), color(0, 0, 0, 0) {}

    VertexColor(Vector3 position, Color color)
        : position(position), color(color) {}

    // ������ ��ġ
    Vector3 position;
    // ������ ��
    Color color;

    // ���� �������� ������ �������ִ� ����
    static D3D11_INPUT_ELEMENT_DESC descs[];
    // ���� �������� ����
    static const uint count = 2;
};

// �ؽ�ó�� �׸�
struct VertexTexture
{
    VertexTexture()
        : position(0, 0, 0), uv(0, 0) {}

    VertexTexture(Vector3 position, Vector2 uv)
        : position(position), uv(uv) {}


    // ������ ��ġ
    Vector3 position;
    // �׸��� ��ǥ
    Vector2 uv;

    // ���� �������� ������ �������ִ� ����
    static D3D11_INPUT_ELEMENT_DESC descs[];
    // ���� �������� ����
    static const uint count = 2;
};