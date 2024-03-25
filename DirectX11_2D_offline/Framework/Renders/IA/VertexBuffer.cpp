#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    // SAFE_RELEASE�� ID3D�� �����ϴ� �������̽��� �����ϴµ�
    // ���Ǹ�, �ش� �������̽����� ���α׷��Ӱ� ����°��� �ƴ�
    // DirectX�� ����� ���� ����� �������� ����̱� ������
    // SAFE_DELETE�� �ƴ϶� SAFE_RELEASE�� ����Ѵ�.
    // i �� �����ϸ� ���� ������ �ض� ��ġ��~~
        SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
    // ��ǲ ������� ���۸� �־��ִ� �Լ�
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
