#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
    // �����Ϸ� ���� �޼����� ������ Blob
    ID3DBlob* error = nullptr;
        
    HRESULT hr = D3DCompileFromFile
    (
        // �������� ���̴� ���� ���
        path.c_str(),
        // ���̴� ������ ��� ������ ��Ÿ���� ������
        nullptr,
        // Include �������̽��� ������ Ŭ������ ��Ÿ���� ������
        nullptr,
        // �������� ���̴� ������ ������
        entryName.c_str(),
        // �������� ���̴� ������ ǥ���� �̸�
        profile.c_str(),
        // ������ ������ �ɼ� // ��� ������ 1�� ����
        D3DCOMPILE_ENABLE_STRICTNESS,
        // ����� ������ ������ ������
        0,
        // ������ ������ ������ Blob
        blob,
        // ������ ���� �޼����� ������ Blob
        &error
    );
    CheckShaderError(hr, error);
    SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
    // HRESULT �� �������� ��� // ���Ĵ� �Ƚ�Ŵ
    if (FAILED(hr))
    {
        // ���� �޼����� ������ ���
        if (error)
        {
            string str = (const char*)error->GetBufferPointer();
            MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
        }
        // ���α׷� ����
        CHECK(false);
    }
}
