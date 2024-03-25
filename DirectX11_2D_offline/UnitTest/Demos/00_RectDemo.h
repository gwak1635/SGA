#pragma once

// IObject는 이 프레임워크에서 사용하는
// 화면에 띄우기 위한 객체를 뜻한다.

#include "Geomatries/Rect.h"

class RectDemo : public IObject
{
public:
    // IObject을(를) 통해 상속됨
    void Init() override;       // 생성자
    void Destroy() override;    // 소멸자
    void Update() override;     // 업데이트
    void Render() override;     // 랜더
    void PostRender() override; // 추가 랜더 // 랜더 끝나고 하는 랜더
    void GUI() override;        // ImGUI 출력

private:
    class Rect* rect = nullptr;
};