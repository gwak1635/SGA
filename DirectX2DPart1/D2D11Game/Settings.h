#pragma once
#include "stdafx.h"


//Singletone Pattern(프로젝트에 하나만 존재한다! 전역에서 접근 가능!)
class Settings final
{
public:
	static Settings& Get()
	{
		static Settings instance;
		return instance;
	}

	auto GetWindowHandle() const -> HWND { return handle; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }

	auto GetWidth() const->const float& { return width; }
	void SetWidth(const float& width) {this->width = width;	}

	auto GetHeight() const->const float& { return height; }
	void SetHeight(const float& height) { this->height = height; }

private:
	Settings() = default;
	~Settings() {};//위에거랑 아래거랑 같음

	HWND handle = nullptr;
	float width = 0.0f;
	float height = 0.0f;
};