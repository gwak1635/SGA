#pragma once

// enum을 이름없이 선언하면 그냥 전역변수 처럼 사용할수 있다.
// 특정 데이터가 가지고있는 x와 y가 아닌 그냥 단독으로 x와 y를 적으면
// 0과 1로 변한된다.
enum
{
    x = 0,
    y
};

struct RectEdge
{
    Vector3 LT;
    Vector3 LB;
    Vector3 RT;
    Vector3 RB;
};

struct AxisData
{
    Vector3 centerPos;  // 축 중앙
    Vector3 axisDir[2]; // 축 방향 // x축 , y축
    float axisLen[2];   // 축 길이 // x축 , y축
};

class BoundingBox
{
public:
    BoundingBox();
    ~BoundingBox();

    void UpdateCollisionData(const Matrix world,
        const Vector3 verticesLocalPosition[]);

    // static 키워드는 해당 함수나 변수를 외부에서 불러와 사용하는것을
    // 허락해주는 키워드라고 볼수있다.
    static bool AABB(BoundingBox* a, BoundingBox* b);
    static bool OBB(BoundingBox* a, BoundingBox* b);

private:
    RectEdge* edge = nullptr;
    AxisData* data = nullptr;
};