#pragma once

// DirectX���� ���̴��� ����� �����ϴ� �������̽�
class IShader
{
public:
    // �������� ���̴� ���� ��� // ������
    virtual void Create(const wstring path, const string entryName) = 0;
    // ��ü �ʱ�ȭ // �Ҹ���
    virtual void Clear() = 0;
    // ���̴� ����
    virtual void SetShader() = 0;

protected:
    // ���̴� ����
    void CompileShader(wstring path, string entryName, string profile,
        ID3DBlob** blob);

    wstring path = L"";     // ���̴� ���� ���
    string entryName = "";  // ������

private:
    // ���̴� ���� üũ
    void CheckShaderError(HRESULT hr, ID3DBlob* error);
};