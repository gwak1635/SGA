#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
    ID3DBlob* error = nullptr;
    
    HRESULT hr = D3DCompileFromFile
    (
        // ���̴� ���� ���
        path.c_str(),
        // ���̴� ������ ����� ��Ÿ�� ������
        nullptr,
        // ����� ������ �ٸ� ������ ������
        nullptr,
        // ������ ��ġ
        // �ַ� VS �ų� PS �ϲ���
        entryName.c_str(),
        // ���̴� ���Ͽ��� ����� ������ �̸�
        profile.c_str(),
        // ������ ��� ���� �ɼ� / �޼��� ������ 1�� ����
        D3DCOMPILE_ENABLE_STRICTNESS,
        // ����� ������ ���Ե� ������ ��� ���� ��ġ
        0,
        // ������ ����� ������ blob
        blob,
        // ������ ���� �޼����� ������ blob
        &error
    );
    // ���� üũ
    CheckShaderError(hr, error);

    SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
    // Hresult�� ������ ���
    // ���Ͽ��� �����͸� �̾ƴµ� �����ߴٸ�
    if (FAILED(hr))
    {
        // ������ �����Ѵٸ�
        if (error)
        {
            // �������� ���̴��� ���° �ٿ��� ������ ������ Ȯ��
            string str = (const char*)error->GetBufferPointer();
            
            // ������ ��ġ�� ���̴� ���� ��� �˷��� ���ڸ� Ȯ�� ��ư�� �Ա� ���
            MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
        }
        // ���α׷� ����
        CHECK(false);
    }
}
