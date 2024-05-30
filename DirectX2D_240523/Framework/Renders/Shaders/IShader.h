#pragma once

// 클래스 이름앞에 I가 붙을경우 인터페이스 클래스라는것을 뜻하며,
// 이러한 인터페이스들은 모든 함수가 순수 가상함수인 특징이 있고
// 인터페스를 상속받는 모든 자식 객체는 반드시 부모객체의 모든 함수를 만들지 않으면
// 객체화 시킬수 없다.

// IShader 는 CPU에서 GPU에게 쉐이더 명령을 내리는 역할
// ShaderBuffer가 건내준 데이터를 IShader가 명령을 내려서 그림을 그리게 되는거라 해석하면
// 편하다.
class IShader
{
public:
    // 생성
    virtual void Create(const wstring path, const string entryName) = 0;
    // 객체 초기화
    virtual void Clear() = 0;
    // 쉐이더에 세팅
    virtual void SetShader() = 0;    
protected:
    void CompileShader(wstring path, string entryName, string profile,
        ID3DBlob** blob);
    
    wstring path = L"";     // 쉐이더 경로
    string entryName = "";  // 진입 결로 // VS로 갈꺼냐, PS로 갈꺼냐
    
private:
    void CheckShaderError(HRESULT hr, ID3DBlob* error);
};