#include "Framework.h"
#include "PixelShader.h"

PixelShader::~PixelShader()
{
    Clear();
}

void PixelShader::Create(const wstring path, const string entryName)
{
    // 쉐이더 경로 받아오기
    this->path = path;
    // 진입점 받아오기
    this->entryName = entryName;

    CompileShader(path, entryName, "ps_5_0", &blob);

    HRESULT hr = DEVICE->CreatePixelShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
    CHECK(hr);
}

void PixelShader::Clear()
{
    SAFE_RELEASE(blob);
    SAFE_RELEASE(shader);
}

void PixelShader::SetShader()
{
    DC->PSSetShader(shader, nullptr, 0);
}
