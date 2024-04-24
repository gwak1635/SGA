#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    // SAFE_RELEASE�� ID3D�� �����ϴ� �������̽��� �����ϴµ�
    // ���Ǹ�, �ش� �������̽����� ���α׷��Ӱ� ����� ���� �ƴ�
    // DirectX�� ����� ���� ����� ���� ���� ����̱� ������
    // delete�� �ƴ϶� release�� ����ϴ� ���̴�.
    SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
    // ��ǲ ������� ���۸� �־��ִ� �Լ�
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
