#pragma once

// 단색의 네모
struct VertexColor
{
    VertexColor()
        : position(0, 0, 0), color(0, 0, 0, 0) {}

    VertexColor(Vector3 position, Color color)
        : position(position), color(color) {}

    // 정점의 위치
    Vector3 position;
    // 정점의 색
    Color color;

    // 정점 데이터의 구조를 서술해주는 역할
    static D3D11_INPUT_ELEMENT_DESC descs[];
    // 정점 데이터의 개수
    static const uint count = 2;
};

// 텍스처의 네모
struct VertexTexture
{
    VertexTexture()
        : position(0, 0, 0), uv(0, 0) {}

    VertexTexture(Vector3 position, Vector2 uv)
        : position(position), uv(uv) {}


    // 정점의 위치
    Vector3 position;
    // 그림의 좌표
    Vector2 uv;

    // 정점 데이터의 구조를 서술해주는 역할
    static D3D11_INPUT_ELEMENT_DESC descs[];
    // 정점 데이터의 개수
    static const uint count = 2;
};