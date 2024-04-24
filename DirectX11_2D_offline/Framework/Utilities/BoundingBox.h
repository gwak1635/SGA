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
    
    // static Ű����� �ش� �Լ��� ������ �ܺο��� �ҷ��ͼ�
    // ����ϴ°��� ������ִ� Ű���� �̴�.
    static bool AABB(BoundingBox* a, BoundingBox* b);

private:
    RectEdge* edge = nullptr;
};