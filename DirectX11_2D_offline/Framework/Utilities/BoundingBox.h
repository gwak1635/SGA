#pragma once

enum//�̸� ��� ����(���ڿ� ��� �ִ� �ű� ������!)
{
    x = 0,y
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
    Vector3 centerPos; //�߾���ǥ
    Vector3 axisDir[2]; //�����
    float axisLen[2]; //�����
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
    static bool OBB(BoundingBox* a, BoundingBox* b);

private:
    RectEdge* edge = nullptr;
    AxisData* data = nullptr;
};