#pragma once

struct RectEdge
{
    Vector3 LT;
    Vector3 LB;
    Vector3 RT;
    Vector3 RB;
};

class BoundingBox
{
public:
    BoundingBox();
    ~BoundingBox();

    void UpdateData(const Matrix world,
        const Vector3 verticesLocalPosition[]);
    
    // static 키워드는 해당 함수나 변수를 외부에서 불러와서
    // 사용하는것을 허락해주는 키워드 이다.
    static bool AABB(BoundingBox* a, BoundingBox* b);

private:
    RectEdge* edge = nullptr;
};