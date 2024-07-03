#pragma once

#include "Geomatries/Note.h"
#include "Geomatries/TextureRect.h"
#include "Geomatries/Rect.h"

class RhythmGame : public IObject
{
public:
    // IObject을(를) 통해 상속됨
    int LanetoJlane(int lane);
    void InitNote(vector<int> lane, vector<float> time);
    void Init() override;
    void Destroy() override;
    void SeeJudge(int j_judge, int lane);
    void NoteJudge(int j_lane);
    void Update() override;
    void Render() override;
    void PostRender() override;
    void GUI() override;
private:
    vector <int> notelane = { 0,1,2,3,4,5 ,1,4};
    vector <float> time = {0.0f,0.5f,1.0f,1.5f,2.0f,2.5f,3.0f,3.125f};
    vector <Note*> note;
    vector <TextureRect*> judge0;
    vector <TextureRect*> judge1;
    vector <Rect*> lane;
    vector <Rect*> keybeam;
    Rect* Judgeline = nullptr;
    int lanethick = 15;
    float baesok=2.0f;
    float onesec = 155 * baesok;
    float guage = 100.f;
};