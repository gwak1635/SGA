#pragma once

#include "Geometries//TextureRect.h"

class TextureDemo : public IObject
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
	TextureRect* tr = nullptr;
};