#pragma once

// Ŭ���� �̸��տ� I�� ������� �������̽� Ŭ������°��� ���ϸ�,
// �̷��� �������̽����� ��� �Լ��� ���� �����Լ��� Ư¡�� �ְ�
// �����佺�� ��ӹ޴� ��� �ڽ� ��ü�� �ݵ�� �θ�ü�� ��� �Լ��� ������ ������
// ��üȭ ��ų�� ����.

// IShader �� CPU���� GPU���� ���̴� ����� ������ ����
// ShaderBuffer�� �ǳ��� �����͸� IShader�� ����� ������ �׸��� �׸��� �Ǵ°Ŷ� �ؼ��ϸ�
// ���ϴ�.
class IShader
{
public:
    // ����
    virtual void Create(const wstring path, const string entryName) = 0;
    // ��ü �ʱ�ȭ
    virtual void Clear() = 0;
    // ���̴��� ����
    virtual void SetShader() = 0;    
protected:
    void CompileShader(wstring path, string entryName, string profile,
        ID3DBlob** blob);
    
    wstring path = L"";     // ���̴� ���
    string entryName = "";  // ���� ��� // VS�� ������, PS�� ������
    
private:
    void CheckShaderError(HRESULT hr, ID3DBlob* error);
};