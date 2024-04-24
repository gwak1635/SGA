#pragma once

#include "IShader.h"

class VertexShader : public IShader
{
public:
    ~VertexShader();
    
    // IShader��(��) ���� ��ӵ�
    void Create(const wstring path, const string entryName) override;
    void Clear() override;
    void SetShader() override;

    ID3D11VertexShader* GetResource() { return shader; }
    ID3DBlob* GetBlob() { return blob; }

private:
    ID3D11VertexShader* shader = nullptr;
    ID3DBlob* blob = nullptr;
};