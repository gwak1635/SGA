#pragma once

#include "Geometries/ShaderTexture.h"

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
};