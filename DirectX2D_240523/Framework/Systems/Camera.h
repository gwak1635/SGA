#pragma once

#include "Geomatries/TextureRect.h"

class Camera : public SingletonBase<Camera>
{
public:
	friend SingletonBase<Camera>;

	void Update();
	void Render();

	void Move();
	void UpdateView();

	const Vector3 GetPosition() { return position; }
	const Vector3 GetMPosition();

	void SetPosition(Vector3 position) 
	{ this->position = position; }

	void SetTarget(TextureRect* target) 
	{ this->target = target; }
	void DelTarget() { this->target = nullptr; }
	TextureRect* GetTarget() { return target; }

private:
	Camera();
	~Camera();

private:
	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;
	
	bool bMove = false;
	float moveSpd = 100.0f;

	TextureRect* target = nullptr;
};