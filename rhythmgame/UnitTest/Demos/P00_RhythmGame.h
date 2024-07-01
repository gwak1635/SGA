#pragma once

#include "Geomatries/Note.h"
#include "Geomatries/TextureRect.h"
#include "Geomatries/Rect.h"

class RhythmGame : public IObject
{
public:
    // IObject을(를) 통해 상속됨
    void Init() override;
    void Destroy() override;
    void SeeJudge(int j_judge);
    void NoteJudge(int j_lane);
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;
private:
    vector <Note*> note;
    vector <TextureRect*> judge;
    vector <Rect*> lane;
    vector <Rect*> keybeam;
    Rect* Judgeline = nullptr;
    float baesok=2.0f;
    float onesec = 155 * baesok;
    float guage = 100.f;
};