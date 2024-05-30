#pragma once

class VertexBuffer
{
public:
    ~VertexBuffer();

    // template<typename T>는 이 다음에 오는 함수에 들어가는 T를
    // 어떤게 들어가든 사용할수 있도록 해주는 기능이다.
    
    // Create에서 템플릿을 사용한 이유는 그릴 사각형에 따라
    // 다른 데이터를 건내줘야 하기 때문이다.
    template<typename T>
    void Create(const vector<T>& vertices,
        const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

    ID3D11Buffer* GetResource() { return buffer; }

    uint GetStride() { return stride; }
    uint GetOffset() { return offset; }
    uint GetCount()  { return count;  }

    void SetIA();

private:
    ID3D11Buffer* buffer = nullptr;

    // 버퍼에서 한 정점의 크기를 나타내는 값
    uint stride = 0;
    // 버퍼에서 읽을 시작 위치
    uint offset = 0;
    // 버퍼에서 읽을 정점의 개수
    uint count  = 0;
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
    stride = sizeof(T);     // 정점 크기 저장
    count = vertices.size();// 정점 개수 저장

    // DESC는 프로그래머가 원하는 목적에 맞게 사용할
    // Dircex데이터들을 만들기 위한 일종의 설계도다.
    D3D11_BUFFER_DESC desc; // 구조체 / struct
    // Desc 메모리 초기화
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

    // desc 설정
    {
        // 사용 용도
        desc.Usage = usage;
        // 사용 목적
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        // 버퍼 크기
        desc.ByteWidth = stride * count;
        // cpu 설정
        // GPU는 모든 데이터 접근할수 있다.
        switch (usage)
        {
            // CPU가 접근할수 없는 버퍼
            // GPU가 수정할수 있는 버퍼
        case D3D11_USAGE_DEFAULT:
            // CPU가 접근할수 없는 버퍼
            // GPU가 수정할수 없는 버퍼
        case D3D11_USAGE_IMMUTABLE:
            break;
            // CPU에서 접근 가능하고 수정할수 있는 버퍼
            // GPU가 수정할수 없는 버퍼
        case D3D11_USAGE_DYNAMIC:
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            break;
            // CPU에서 접근 가능하고 수정할수 있는 버퍼
            // GPU가 수정할수 있는 버퍼
        case D3D11_USAGE_STAGING:
            desc.CPUAccessFlags =
                D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
            break;
        }
    }

    // 생성
    {
        // D3D11_SUBRESOURCE_DATA는 다양한 데이터를 임시로
        // 보관할수있는 구조체이다.
        D3D11_SUBRESOURCE_DATA subData;
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

        subData.pSysMem = vertices.data();

        // HRESULT는 해당 작업이 정상적으로 수행됐는지 판단하는
        // 자료형이며, 작업이 끝난 변수를 CHECK에 집어넣어
        // 만약, 작업이 정상적으로 진행되지 않았다면
        // 실행시 에러메세지가 출력된다.
        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,
            &buffer);
        CHECK(hr);
    }
}
