#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    // SAFE_RELEASE는 ID3D로 시작하는 인터페이스를 헤제하는데
    // 사용되며, 해당 인터페이스들은 프로그래머가 만드는것이 아닌
    // DirectX가 만들어 놓은 기능을 빌려오는 방식이기 때문에
    // SAFE_DELETE가 아니라 SAFE_RELEASE를 사용한다.
    // i 로 시작하면 대충 릴리즈 해라 눈치껏~~
        SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
    // 인풋 어셈블러에 버퍼를 넣어주는 함수
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
