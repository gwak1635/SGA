#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
    edge = new RectEdge();
}

BoundingBox::~BoundingBox()
{
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
