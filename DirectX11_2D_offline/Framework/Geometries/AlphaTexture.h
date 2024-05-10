#pragma once

#include "TextureRect.h"

class AlphaBuffer : public ShaderBuffer
{
public:
	AlphaBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		data.alphaColor = 0xff73e6e1; // 배경색
		data.alpha = 0.0f;
	}

	float GetAlpha() { return data.alpha; }
	float* GetAlphaPtr() { return &data.alpha; }
	void SetAlpha(float alpha) { data.alpha = alpha; }

	Color GetAlphaColor() { return data.alphaColor; }
	void SetAlpha(Color color) { data.alphaColor = color; }

	struct Data
	{
		Color alphaColor;//16

		float alpha;//4

		Vector3 dummy;// 패딩 데이터(32비트 채우기용)
	};
private:
	Data data;

};

class AlphaTexture : public TextureRect
{
public:
	AlphaTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	~AlphaTexture();

	void Update();
	void Render();
	void GUI();

	AlphaBuffer* GetAB() { return ab; }
private:
	AlphaBuffer* ab = nullptr;
};