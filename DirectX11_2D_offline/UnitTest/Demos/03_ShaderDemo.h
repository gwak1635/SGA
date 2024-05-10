#pragma once

#include "Geometries/ShaderTexture.h"
#include "Geometries/AlphaTexture.h"
class ShaderDemo : public IObject
{
public:
	// IObject��(��) ���� ��ӵ�
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

private:
	ShaderTexture* st = nullptr;
	AlphaTexture* at = nullptr;
};