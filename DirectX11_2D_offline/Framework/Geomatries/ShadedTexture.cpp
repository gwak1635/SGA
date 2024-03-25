#include "Framework.h"
#include "ShadedTexture.h"


ShadedTexture::ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path)
    : TextureRect(position, size, rotation, path)
{
    sb = new ShadedBuffer();
    sb->SetTextureSize(Vector2(size.x, size.y));
    SetShader(ShaderPath + L"TextureShader.hlsl");
}

ShadedTexture::~ShadedTexture()
{
    SAFE_DELETE(sb);
}

void ShadedTexture::Update()
{
    __super::Update();
}

void ShadedTexture::Render()
{
    sb->SetPSBuffer(0);
    __super::Render();
}

void ShadedTexture::GUI()
{
    ImGui::Begin("Shaded");
    {
        ImGui::RadioButton(
            "Normal", sb->GetSelectionPtr(), 1);
        ImGui::RadioButton(
            "Gray", sb->GetSelectionPtr(), 2);
        ImGui::RadioButton(
            "Negative", sb->GetSelectionPtr(), 3);
        ImGui::RadioButton(
            "Blur", sb->GetSelectionPtr(), 4);
        ImGui::RadioButton(
            "PivotRL", sb->GetSelectionPtr(), 5);
        ImGui::RadioButton(
            "PivotUD", sb->GetSelectionPtr(), 6);

        ImGui::SliderInt(
            "BlurCount", sb->GetBlurCountPtr(), 1, 20);
    }
    ImGui::End();

}
