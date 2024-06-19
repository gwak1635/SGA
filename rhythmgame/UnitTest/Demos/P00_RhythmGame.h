#pragma once

#include "Geomatries/Note.h"
#include "Geomatries/TextureRect.h"
#include "Geomatries/Rect.h"

class RhythmGame : public IObject
{
public:
    // IObject��(��) ���� ��ӵ�
    void Init() override;
    void Destroy() override;
    void NoteJudge(int j_lane);
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;
private:
    vector <Note*> note;
    vector <Rect*> lane;
    Rect* Judgeline = nullptr;
    float baesok=2.0f;
};