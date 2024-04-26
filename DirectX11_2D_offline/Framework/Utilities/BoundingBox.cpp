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

void BoundingBox::UpdateData(const Matrix world, const Vector3 verticesLocalPosition[])
{
    // AABB
    {
        // LocalPos -> WorldPos
        D3DXVec3TransformCoord(&edge->LT,
            &verticesLocalPosition[3], &world);
        D3DXVec3TransformCoord(&edge->LB,
            &verticesLocalPosition[0], &world);
        D3DXVec3TransformCoord(&edge->RT,
            &verticesLocalPosition[1], &world);
        D3DXVec3TransformCoord(&edge->RB,
            &verticesLocalPosition[2], &world);
    }

    
    //OBB
    {
        //CenterPos Vector
        {
            data->centerPos = Vector3
            (
                (edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) * 0.25f,
                (edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) * 0.25f,
                0
            );
        }

        //AxisDir
        {
            //Normal이 들어가면 정규화(0~1화)
            D3DXVec3TransformNormal(&data->axisDir[x], &Vector3(1, 0, 0), &world);
            D3DXVec3TransformNormal(&data->axisDir[y], &Vector3(0, 1, 0), &world);
            //월드상에서 up좌표와 right좌표가반환됨.

            D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
            D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
            //불안정한 데이터를 교정하는 것
        }

        //AxisLen
        {
            Vector3 unitAxis[2] = { data->axisDir[x] ,data->axisDir[y] };

            Vector3 verticesPos[4] = { edge->LT ,edge->LB ,edge->RT ,edge->RB };

            float minValues[2] = { INT_MAX, INT_MAX };
            float maxValues[2] = { INT_MIN, INT_MIN };

            for (int i = 0; i < 4; i++)
            {
                Vector3 point = verticesPos[i];

                for (int j = 0; j < 2; j++)
                {
                    float projection = D3DXVec3Dot(&point, &unitAxis[j]);

                    if (projection < minValues[j])
                        minValues[j] = projection;
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

    if (aEdge.LT.x <= bEdge.RB.x &&
        aEdge.LT.y >= bEdge.RB.y &&
        aEdge.RB.x >= bEdge.LT.x &&
        aEdge.RB.y <= bEdge.LT.y)
        return true;

    return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
    if (a == nullptr || b == nullptr) return false;

    AxisData aData = *a->data;
    AxisData bData = *b->data;

    Vector3 centerDir, axis;
    float centerProjDist, r1, r2;


    //a와 b사이의 거리
    centerDir = aData.centerPos - bData.centerPos;

    //arect:x축
    {
        axis = aData.axisDir[x];

        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = aData.axisLen[x];
        r2 = abs(D3DXVec3Dot(&bData.axisDir[x], &axis) * bData.axisLen[x]) +
            abs(D3DXVec3Dot(&bData.axisDir[y], &axis) * bData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    //arect:y축
    {
        axis = aData.axisDir[y];

        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = aData.axisLen[y];
        r2 = abs(D3DXVec3Dot(&bData.axisDir[x], &axis) * bData.axisLen[x]) +
            abs(D3DXVec3Dot(&bData.axisDir[y], &axis) * bData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    //brect:x축
    {
        axis = bData.axisDir[x];

        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = bData.axisLen[x];
        r2 = abs(D3DXVec3Dot(&aData.axisDir[x], &axis) * aData.axisLen[x]) +
            abs(D3DXVec3Dot(&aData.axisDir[y], &axis) * aData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    //brect:y축
    {
        axis = bData.axisDir[y];

        centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

        r1 = bData.axisLen[y];
        r2 = abs(D3DXVec3Dot(&aData.axisDir[x], &axis) * aData.axisLen[x]) +
            abs(D3DXVec3Dot(&aData.axisDir[y], &axis) * aData.axisLen[y]);

        if (centerProjDist > r1 + r2)
            return false;
    }

    return true;
}

//OBB충돌: 직사각형-마름모 충돌
//'닿지 않는' 평행선에 투영시켜 '모두' 닿았는지 안 닿았는지 확인하는 것
//'가장 작거나 큰 x, y를 알아내는 법
//원 충돌: 반지름+반지름이 거리보다 크면 충돌
//Right벡터, Up벡터 뽑아내서 
//무겁습니다. 4.5배정도 무겁습니다.
//돌아간 총알을 구현할 때, 마름모로 회전된 것보다, 그냥 직사각형 히트박스를 넣는게 더 좋음...(총알이 한두개도 아니고 최적화 해야지)
//화면에 있는 모든 오브젝트는 항상 연산 상태.
//총알이 OBB연산을 하면 모든 객체와 OBB 충돌 연산을 한다!!!!

//게임 개발이 ㅈ같은 이유: 방법이 졸ㄹㄹㄹ라게 많음

//해당 키를 누른 직후에 충돌이 되었다: 이속- or 해당 키 비활성화
