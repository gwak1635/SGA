#pragma once

// IObject�� �� �����ӿ�ũ���� ����ϴ�
// ȭ�鿡 ���� ���� ��ü�� ���Ѵ�.

#include "Geomatries/Rect.h"

class RectDemo : public IObject
{
public:
    // IObject��(��) ���� ��ӵ�
    void Init() override;       // ������
    void Destroy() override;    // �Ҹ���
    void Update() override;     // ������Ʈ
    void Render() override;     // ����
    void PostRender() override; // �߰� ���� // ���� ������ �ϴ� ����
    void GUI() override;        // ImGUI ���

private:
    class Rect* rect = nullptr;
};