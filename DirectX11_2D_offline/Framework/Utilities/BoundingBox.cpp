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
        // CenterPos Vector Update // 축 중심 확인
        {
            data->centerPos = Vector3
            (
                (edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) * 0.25f,
                (edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) * 0.25f,
                0
            );
        }

        // AxisDir Update // 축 방향 확인
        {
            // Normal이 들어간 대부분은 정규화하는 함수이다.
            // 정규화는 모든 값을 0 ~ 1 사이로 바꾸는 과정이다.
            D3DXVec3TransformNormal(&data->axisDir[x],
                &Vector3(1, 0, 0), &world);
            D3DXVec3TransformNormal(&data->axisDir[y],
                &Vector3(0, 1, 0), &world);

            D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
            D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
        }

        // AxisLen Update // 축 길이 확인
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

                    // 네모가 가지고있는 x축,y축의 최소값 찾기
                    if (projection < minValues[j])
                        minValues[j] = projection;

                    // 네모가 가지고있는 x축,y축의 최대값 찾기
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

    // 회전하지 않은 사각형들의 충돌은 각각의 사각형이 가진
    // 가장 큰 xy와 가장 작은 xy를 비교하는것으로 가능하며
    // 예를들어 A의 LT.x 즉 A의 가장 작은 X값이 B의 가장 큰 X값보다
    // 숫자가 크다면 절대로 충돌이 일어날수 없고
    // A의 LT.y 즉 A의 가장 높은 Y값이 B의 가장 낮은 Y값 RB의 Y보다 작다면
    // 그거또한 절대로 충돌이 일어날수 없다는 내용들 이용해
    // 충돌검사를 실행한다.
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

    // a와 b사이의 거리
    centerDir = ad.centerPos - bd.centerPos;

    // a Rect : X축
    {
        axis = ad.axisDir[x];

        // 실제 비교할 사이 거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = ad.axisLen[x];
        r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
            abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // a Rect : Y축
    {
        axis = ad.axisDir[y]; // <- 이거 Y로 바꿈

        // 실제 비교할 사이 거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = ad.axisLen[y]; // <- 이거 Y로 바꿈
        r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
            abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // b Rect : X축
    {
        axis = bd.axisDir[x];

        // 실제 비교할 사이 거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = bd.axisLen[x];
        r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
            abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    // b Rect : Y축
    {
        axis = bd.axisDir[y];

        // 실제 비교할 사이 거리
        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = bd.axisLen[y];
        r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
            abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    return true;
}
