#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // Vertices
    {
        // vector.assign 은 벡터의 크기를 재설정
        vertices.assign(4, VertexColor());

        // 좌 하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].color = Color(1, 0, 0, 1); // R, G, B , A

        // 우 상단
        vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
        vertices[1].color = Color(1, 0, 0, 1);

        // 우 하단
        vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
        vertices[2].color = Color(1, 0, 0, 1);

        // 좌 상단
        vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
        vertices[3].color = Color(1, 0, 0, 1);
    }

    // VertexBuffer
    {
        vb = new VertexBuffer();
        vb->Create(vertices, D3D11_USAGE_DYNAMIC);
    }

    // IndexBuffer
    {
        indices = { 0,1,2,0,3,1 };

        ib = new IndexBuffer();
        ib->Create(indices, D3D11_USAGE_IMMUTABLE);
    }   

    // VertexShader
    {
        vs = new VertexShader();

        // 쉐이더경로 + 실행 시킬 쉐이더 파일 이름, 실행할 함수 이름
        vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
    }

    // InputLayout
    {
        il = new InputLayout();
        il->Create(VertexColor::descs, VertexColor::count,
            vs->GetBlob());
    }

    // PixelShader
    {
        ps = new PixelShader();
        ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
    }

    // WolrdBuffer
    {
        wb = new WorldBuffer();
    }

    // Collision
    {
        edge = new RectEdge();
        collision = new BoundingBox();

        // 정점 위치 전달
        for (int i = 0; i < 4; i++)
            verticesPosition[i] = vertices[i].position;
    }


}

Rect::~Rect()
{
    SAFE_DELETE(collision);
    SAFE_DELETE(edge);

    SAFE_DELETE(wb);

    SAFE_DELETE(ps);
    SAFE_DELETE(il);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void Rect::Update()
{   // 업데이트에는 주로 이 객체가 매 프레임마다 할 행동들을 적어둔다
    // Move();         // 이 객체는 움직일꺼고
    UpdateWorld();  // 월드상에 배치될 것이다.

    // 충돌 박스에 데이터 전달
    collision->UpdateCollisionData(world, verticesPosition);
}

void Rect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    // 삼각형을 어떻게 그릴지 정해주는 함수
    DC->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    // 실질적으로 그림을 그리는 코드
    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::Move()
{
    float mSpd = 100;

    // 키보드로 W를 누르고 있을 경우
    // Get()->Down == 눌렀을때 한번만
    // Get()->Up == 눌렀다 땠을때 한번만
    if (Keyboard::Get()->Press('W'))
    {
        // Time::Get()->Delta()는 프레임과 프레임 사이의 시간을 반환
        // 이 값이 계속 더해져 1이 됐다면 1초가 지났다는 이야기
        position.y += mSpd * Time::Delta();

        // 선입력으로 S가 있었는지 확인
        // 없었다면
        if (Keyboard::Get()->Press('S') && moveD == false)
        {
            // 이동값을 2배로 내리면
            // 위에 있는 증가한 값이 사라지고 아래로 간다.
            position.y -= (mSpd * 2) * Time::Delta();
        }
    }    
    else if (Keyboard::Get()->Press('S'))
    {
        moveD = true;
        position.y -= mSpd * Time::Delta();
    }

    if (Keyboard::Get()->Up('S')) moveD = false;

    if (Keyboard::Get()->Press('A'))
    {
        position.x -= mSpd * Time::Delta();
        if (Keyboard::Get()->Press('D') && !moveR)
        {
            position.x += (mSpd * 2) * Time::Delta();
        }
    }
    else if (Keyboard::Get()->Press('D'))
    {
        moveR = true;
        position.x += mSpd * Time::Delta();
    }

    if (Keyboard::Get()->Up('D')) moveR = false;

    // 키보드로 스페이스바를 눌렀을 경우
    // 일반적인 알파벳 키는 ' ' 문자로 전달하고
    // 그외의 다양한 키들 (F1 , SAPCE, CTRL) 같은건 VK 가상키로 전달한다.
    if (Keyboard::Get()->Down(VK_SPACE))
    {
        /*
        모든 점프는 기본적으로 bool값을 이용해
        스페이스바를 눌렀을경우 해당 bool값을 true로 바꾸며
        해당 bool값이 true일때 점프 이동을 실행하는것을 기본으로 둔다.

        만약, 점프를 누르고있는동안 점프의 높이가 점점 증가하는 방식의
        점프를 만들고싶다면 bool값을 사용하지 않아도 된다.

        점프 만드는법 1. 점프 시간 이용하기 
        // 일정한 시간의 점프 구현 가능 
        1. 스페이스바를 눌렀을경우 일정시간 동안 위로 간다.
        (Time::Delta가 계속 더해지다가 1이 되면 1초가 지난단거임)
        2. 일정 시간이 지나면 다시 원래있던 곳으로 천천히 내려온다.

        점프 만드는법 2. 중력 이용하기 
        // 감속가속이 쉬운 점프 구현 가능
        1. 스페이스바를 눌렀을경우 중력값만큼 이동을 시작하기
        2. 중력값은 처음에 +였다가 시간이 지날수록 점점 -로 바뀐다.

        점프 만드는법 3. 특정 거리까지 이동하기 
        // 목적지 도달이 쉬운 점프 구현 가능
        1. 스페이스바를 눌렀을경우 현재 자신의 위치에서 특정 좌표까지
        서서히 이동
        2. 해당 좌표 도달시 다시 천천히 떨어짐
        */
    }

}

void Rect::GUI()
{
    // ImGui를 이용해 UI를 만들어내는 기능과 코드들
    
    // ImGui 코드들을 이용해 UI를 만들기위해 먼저 실행해야하는 함수
    ImGui::Begin("Rect", &bOpen);
    {
        ImGui::Text(MakeLabel("Rect").c_str());
        ImGui::SliderFloat2(MakeLabel("Pos").c_str(), position,0, WinMaxWidth);
        ImGui::SliderFloat2(MakeLabel("Size").c_str(), size, 0, WinMaxWidth);
        ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation,
            0, 360.0f);

        // 특정 UI기능이 작동했다면 특정 함수를 실행하게 할수도 있음
        if (ImGui::ColorPicker4(MakeLabel("Color").c_str(), color))
            UpdateColor();
    }
    // ImGui의 UI만드는게 끝났다는것을 알려줄 함수
    ImGui::End();
}

void Rect::UpdateColor()
{
    D3D11_MAPPED_SUBRESOURCE subResource;
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0,
        &subResource);
    { // 맵핑중인 공간
        for (VertexColor& v : vertices)
        {
            // vertices에다가 변경된 color값을 넣어주고
            v.color = color;
        }

        // 변경된 color값을 vertices에다가 넣어준다.
        memcpy(subResource.pData, vertices.data(),
            vb->GetCount() * vb->GetStride());
    }
    DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLabel(string label)
{
    // 자기 자신의 주소를 매게 변수로 받은 라벨 뒤에 적어넣는다.
    string Label = label + "##" + to_string((uint)this);
    return Label;
}

void Rect::UpdateWorld()
{
    // 로컬 크기를 월드상 크기로 변경
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    // 로컬 회전값을 월드상 회전값으로 변경
    D3DXMatrixRotationZ(&R, rotation);
    // 로컬 위치를 월드상 위치로 변경
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    // SRT순서가 아니면 정상적으로 나오지 않음
    world = S * R * T;
    wb->SetWorld(world);
}

void Rect::SetColor(Color color)
{
    this->color = color;
    UpdateColor();
}
