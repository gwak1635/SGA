#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
    edge = new RectEdge();
    data = new AxisData();
}

BoundingBox::~BoundingBox()
{
    SAFE_DELETE(data);
    SAFE_DELETE(edge);
}

void BoundingBox::UpdateCollisionData(const Matrix world, const Vector3 verticesLocalPosition[])
{
    // AABB
    {
        // LocalPos -> WorldPos
        D3DXVec3TransformCoord(&edge->LT, &verticesLocalPosition[3], &world);
        D3DXVec3TransformCoord(&edge->LB, &verticesLocalPosition[0], &world);
        D3DXVec3TransformCoord(&edge->RT, &verticesLocalPosition[1], &world);
        D3DXVec3TransformCoord(&edge->RB, &verticesLocalPosition[2], &world);
    }

    // OBB
    {
        // CenterPos Vector Update // �� �߽� Ȯ��
        {
            data->centerPos = Vector3
            (
                (edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) * 0.25f,
                (edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) * 0.25f,
                0
            );
        }

        // AxisDir Update // �� ���� Ȯ��
        {
            // Normal�� �� ��κ��� ����ȭ�ϴ� �Լ��̴�.
            // ����ȭ�� ��� ���� 0 ~ 1 ���̷� �ٲٴ� �����̴�.
            D3DXVec3TransformNormal(&data->axisDir[x],
                &Vector3(1, 0, 0), &world);
            D3DXVec3TransformNormal(&data->axisDir[y],
                &Vector3(0, 1, 0), &world);

            D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
            D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
        }

        // AxisLen Update // �� ���� Ȯ��
        {
            Vector3 unitAxis[2] =
            { data->axisDir[x], data->axisDir[y] };

            Vector3 verticesPos[4] =
            { edge->LT, edge->LB, edge->RT, edge->RB };

            float minValues[2] = { INT_MAX, INT_MAX };
            float maxValues[2] = { INT_MIN, INT_MIN };

            for (int i = 0; i < 4; i++)
            {
                Vector3 point = verticesPos[i];

                for (int j = 0; j < 2; j++)
                {
                    float projection =
                        D3DXVec3Dot(&point, &unitAxis[j]);

                    // �׸� �������ִ� x��,y���� �ּҰ� ã��
                    if (projection < minValues[j])
                        minValues[j] = projection;

                    // �׸� �������ִ� x��,y���� �ִ밪 ã��
                    if (projection > maxValues[j])
                        maxValues[j] = projection;
                }
            }

            data->axisLen[x] = (maxValues[x] - minValues[x]) * 0.5f;
            data->axisLen[y] = (maxValues[y] - minValues[y]) * 0.5f;
        }
    }
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
    if (a == nullptr || b == nullptr) return false;

    RectEdge aEdge = *a->edge;
    RectEdge bEdge = *b->edge;

    // ȸ������ ���� �簢������ �浹�� ������ �簢���� ����
    // ���� ū xy�� ���� ���� xy�� ���ϴ°����� �����ϸ�
    // ������� A�� LT.x �� A�� ���� ���� X���� B�� ���� ū X������
    // ���ڰ� ũ�ٸ� ����� �浹�� �Ͼ�� ����
    // A�� LT.y �� A�� ���� ���� Y���� B�� ���� ���� Y�� RB�� Y���� �۴ٸ�
    // �װŶ��� ����� �浹�� �Ͼ�� ���ٴ� ����� �̿���
    // �浹�˻縦 �����Ѵ�.
    if (aEdge.LT.x <= bEdge.RB.x &&
        aEdge.LT.y >= bEdge.RB.y &&
        aEdge.RB.x >= bEdge.LT.x &&
        aEdge.RB.y <= bEdge.LT.y)
        return true;

    return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
    AxisData ad = *a->data;
    AxisData bd = *b->data;

    Vector3 centerDir, axis;
    float centerProjDist, r1, r2;

    // a�� b������ �Ÿ�
    centerDir = ad.centerPos - bd.centerPos;

    // a Rect : X��
    {
        axis = ad.axisDir[x];

        // ���� ���� ���� �Ÿ�
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = ad.axisLen[x];
        r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
            abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // a Rect : Y��
    {
        axis = ad.axisDir[y]; // <- �̰� Y�� �ٲ�

        // ���� ���� ���� �Ÿ�
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = ad.axisLen[y]; // <- �̰� Y�� �ٲ�
        r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
            abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // b Rect : X��
    {
        axis = bd.axisDir[x];

        // ���� ���� ���� �Ÿ�
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = bd.axisLen[x];
        r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
            abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // b Rect : Y��
    {
        axis = bd.axisDir[y];

        // ���� ���� ���� �Ÿ�
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = bd.axisLen[y];
        r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
            abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    return true;
}
