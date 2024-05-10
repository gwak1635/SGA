#pragma once

#include "TextureRect.h"

class STBuffer : public ShaderBuffer
{
public:
	STBuffer() :ShaderBuffer(&data, sizeof(data))
	{
		data.selection = 1;
		data.blurCount = 1;
		data.textureSize = Vector2(0, 0);
	}

	int* GetSelPtr() { return &data.selection; }
	int* GetBCPtr() { return &data.blurCount; }

	void SetTextureSize(Vector2 size) { data.textureSize = size; }
	struct Data {
		int selection;			//���̴� ȿ�� ���� ��ȣ

		int blurCount;			//���� ����
		Vector2 textureSize;	//�׸��� ũ��
	};

private:
	Data data;

};

class ShaderTexture : public TextureRect
{
public:
	ShaderTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	~ShaderTexture();

	void Update();
	void Render();
	void GUI();

private:
	STBuffer* sb = nullptr;
};