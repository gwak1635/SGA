#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
{
	Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);
	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
    // 원본 텍스쳐 정보
    D3D11_TEXTURE2D_DESC srvDesc;
    texture->GetDesc(&srvDesc);

    // 원본 텍츠쳐 복사본
    D3D11_TEXTURE2D_DESC destDesc;
    ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

    // 복사본 desc 설정
    destDesc.Usage = D3D11_USAGE_STAGING;
    destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    destDesc.Width = srvDesc.Width;
    destDesc.Height = srvDesc.Height;
    destDesc.MipLevels = 1;
    destDesc.ArraySize = 1;
    destDesc.Format = srvDesc.Format;
    destDesc.SampleDesc = srvDesc.SampleDesc;

    ID3D11Texture2D* destTex = nullptr;

    HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr,
        &destTex);
    CHECK(hr);
    // 원본 texture를 복사본인 destTex에 집어 넣는다.
    D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

    UINT* colors = new UINT[destDesc.Width * destDesc.Height];

    D3D11_MAPPED_SUBRESOURCE subRe;
    DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subRe);
    {
        // 그림의 픽셀 색상을 전부 추출
        memcpy(colors, subRe.pData, sizeof(UINT) *
            destDesc.Width * destDesc.Height);
    }
    DC->Unmap(destTex, 0);

    // 이미지 가로 * 세로 즉, 픽셀 개수
    int pixelNum = destDesc.Width * destDesc.Height;

    // OpenGL과 호환되기 위해 색상 위치를 수정
    {
        UINT* alpha = new UINT[destDesc.Width * destDesc.Height];
        UINT* red = new UINT[destDesc.Width * destDesc.Height];
        UINT* green = new UINT[destDesc.Width * destDesc.Height];
        UINT* blue = new UINT[destDesc.Width * destDesc.Height];

        for (int i = 0; i < pixelNum; i++)
        {
            alpha[i] = (colors[i] & 0xFF000000);
            red[i] = (colors[i] & 0x00FF0000);
            green[i] = (colors[i] & 0x0000FF00);
            blue[i] = (colors[i] & 0x000000FF);

            // OpenGL은 ARGB가 아닌 ABGR 순서이기 때문에
            // R과 B의 위치를 바꾼다
            red[i] = colors[i] >> 16;
            blue[i] = colors[i] << 16;

            colors[i] = alpha[i] | red[i] | green[i] | blue[i];
        }
        pixels->assign(&colors[0], &colors[pixelNum - 1]);
    }

    SAFE_DELETE_ARRAY(colors);
    SAFE_DELETE(destTex);
}