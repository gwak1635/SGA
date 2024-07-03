#include "stdafx.h"
#include "P00_RhythmGame.h"

//게이지를 만들어야 한다
//파일 입출력을 통해 채보 데이터 파일을 만들어 보자!
int RhythmGame::LanetoJlane(int lane) {
    if (lane == 0 || lane == 1 || lane == 4) {
        return 0;
    }
    else {
        return 1;
    }
}



void RhythmGame::InitNote(vector<int> lane, vector<float> time)
{
    for (int i = 0; i < lane.size(); i++)
    {
        float x;
        if (LanetoJlane(lane[i])==1) {
            x = WinMaxWidth * 0.5f + 75 + lanethick / 2;
        }
        else {
            x = WinMaxWidth * 0.5f - 75 - lanethick / 2;
        }
         
        note.push_back(new Note({ x, 720 + onesec*time[i], 0},
            { 150.0f,30.0f,1 }, 0, lane[i])
        );
    }
}

void RhythmGame::Init()
{
    {
        //라인 3개(레인 2개) 만들기
        lane.push_back(new Rect(
            Vector3(WinMaxWidth * 0.5f - 150 - lanethick, WinMaxHeight * 0.5f, 0),
            Vector3(lanethick, WinMaxHeight, 1), 0.0f)
        );
        lane.push_back(new Rect(
            Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0),
            Vector3(lanethick, WinMaxHeight, 1), 0.0f)
        );
        lane.push_back(new Rect(
            Vector3(WinMaxWidth * 0.5f + 150 + lanethick, WinMaxHeight * 0.5f, 0),
            Vector3(lanethick, WinMaxHeight, 1), 0.0f)
        );
        for (Rect* r : lane)
        {
            r->SetColor(Color(0, 0, 0, 1));
            r->UpdateWorld();
        }
    }
    //저지라인의 좌표: 100
    Judgeline=new Rect(
        Vector3(WinMaxWidth * 0.5f, 100, 0),
        Vector3(lanethick+300, lanethick, 1), 0.0f);

    Judgeline->SetColor(Color(1, 0, 0, 1));
    Judgeline->UpdateWorld();

    {
        keybeam.push_back(new Rect(
            Vector3(WinMaxWidth * 0.5f - 75 - lanethick*0.5f, 40, 0),
            Vector3(150, 80, 1), 0.0f)
        );
        keybeam.push_back(new Rect(
            Vector3(WinMaxWidth * 0.5f + 75 + lanethick * 0.5f, 40, 0),
            Vector3(150, 80, 1), 0.0f)
        );
        for (Rect* r : keybeam)
        {
            r->SetColor(Color(1, 1, 1, 1));
            r->UpdateWorld();
        }
    }
    
    InitNote(notelane,time);
    for (Note* r : note)
    {
        r->UpdateWorld();
    }

    {
        judge0.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f - 75 - lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\hexed.png")
        );
        judge0.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f - 75 - lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\react.png")
        );
        judge0.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f - 75 - lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\stray.png")
        );
        judge0.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f - 75 - lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\miss.png")
        );
        for (TextureRect* r : judge0)
        {
            r->UpdateWorld();
            r->SetLoading(false);
        }
    }
    {
        judge1.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f + 75 + lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\hexed.png")
        );
        judge1.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f + 75 + lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\react.png")
        );
        judge1.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f + 75 + lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\stray.png")
        );
        judge1.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f + 75 + lanethick * 0.5f, 150, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\miss.png")
        );
        for (TextureRect* r : judge1)
        {
            r->UpdateWorld();
            r->SetLoading(false);
        }
    }
}

void RhythmGame::Destroy()
{
    for (TextureRect* r : judge1)
    {
        SAFE_DELETE(r);
    }
    for (TextureRect* r : judge0)
    {
        SAFE_DELETE(r);
    }
    for (TextureRect* r : note)
    {
        SAFE_DELETE(r);
    }
    for (Rect* r : keybeam)
    {
        SAFE_DELETE(r);
    }
    SAFE_DELETE(Judgeline);
    for (Rect* r : lane)
    {
        SAFE_DELETE(r);
    }
    
}

void RhythmGame::SeeJudge(int j_judge, int lane) {
    switch (lane) {
    case 0:
        for (TextureRect* r : judge0)
        {
            r->SetLoading(false);
        }
        judge0[j_judge]->SetLoading(true);
        break;
    case 1:
        for (TextureRect* r : judge1)
        {
            r->SetLoading(false);
        }
        judge1[j_judge]->SetLoading(true);
        break;
    }
    
}



void RhythmGame::NoteJudge(int j_lane)
{
    int judgelane = LanetoJlane(j_lane);

    Note* Anote = nullptr;
    for (Note* r : note) {
        if (r->GetLoading()) {
            if (r->GetLane() == j_lane && (100 - (onesec * 0.120) <= r->GetPosition().y && r->GetPosition().y <= 100 + (onesec * 0.120)))
            {
                if (Anote == nullptr) { Anote = r; }
                if (Anote->GetPosition().y > r->GetPosition().y) { Anote = r; }
            }
        }
    }
    if (Anote == nullptr) {}
    else if (100 - (onesec * 0.040) <= Anote->GetPosition().y && Anote->GetPosition().y <= 100 + (onesec * 0.040))
    {
        
        SeeJudge(0, judgelane);
        Anote->SetLoading(false);
    }
    else if (100 - (onesec * 0.080) <= Anote->GetPosition().y && Anote->GetPosition().y <= 100 + (onesec * 0.080))
    {
        //react 판정
        SeeJudge(1, judgelane);
        Anote->SetLoading(false);
    }
    else {
        //배드 판정
        SeeJudge(2, judgelane);
        Anote->SetLoading(false);
    }
}

void RhythmGame::Update()
{

    if (Keyboard::Get()->Down('D')) {
        NoteJudge(0);
    }
    if (Keyboard::Get()->Down('F')) {
        NoteJudge(1);
    }
    if (Keyboard::Get()->Down('J')) {
        NoteJudge(2);
    }
    if (Keyboard::Get()->Down('K')) {
        NoteJudge(3);
    }
    if (Keyboard::Get()->Down('D')&&Keyboard::Get()->Press('F')
        || Keyboard::Get()->Down('F') && Keyboard::Get()->Press('D'))
    {
        NoteJudge(4);
    }
    if (Keyboard::Get()->Down('J') && Keyboard::Get()->Press('K')
        || Keyboard::Get()->Down('K') && Keyboard::Get()->Press('J'))
    {
        NoteJudge(5);
    }
    

    for (TextureRect* r : judge0)
    {
        if (r->GetLoading()) {
            r->Update();
        }  
    }
    for (TextureRect* r : judge1)
    {
        if (r->GetLoading()) {
            r->Update();
        }
    }

    for (Note* r : note)
    {
        if (r->GetLoading()) {
            r->NoteFall(baesok);
                        
            //스캔해서 '판정 범위' 맨 밑에 있는 노트를 찾아 냄
            if (r->GetPosition().y < 100 - (onesec * 0.120))
            {
                int judgelane = LanetoJlane(r->GetLane());

                r->SetLoading(false);
                SeeJudge(3, judgelane);
            }

            r->Update();
        }
    } 

    for (Rect* r : keybeam)
    {
        if (Keyboard::Get()->Press('D') && Keyboard::Get()->Press('F'))
        {
            keybeam[0]->SetColor(Color(0.9, 0.9, 0, 1));
        }
        else if (Keyboard::Get()->Press('D'))
        {
            keybeam[0]->SetColor(Color(0, 0.6, 0.95, 1));
        }
        else if (Keyboard::Get()->Press('F'))
        {
            keybeam[0]->SetColor(Color(0.9, 0, 0.3, 1));
        }
        else
        {
            keybeam[0]->SetColor(Color(1, 1, 1, 1));
        }

        if (Keyboard::Get()->Press('J') && Keyboard::Get()->Press('K'))
        {
            keybeam[1]->SetColor(Color(0.9, 0.9, 0, 1));
        }
        else if (Keyboard::Get()->Press('K'))
        {
            keybeam[1]->SetColor(Color(0, 0.6, 0.95, 1));
        }
        else if (Keyboard::Get()->Press('J'))
        {
            keybeam[1]->SetColor(Color(0.9, 0, 0.3, 1));
        }
        else
        {
            keybeam[1]->SetColor(Color(1, 1, 1, 1));
        }

        r->Update();
    }




    for (Rect* r : lane)
    {
        r->Update();
    }
    Judgeline->Update();
}

void RhythmGame::Render()
{
      
    for (Rect* r : keybeam)
    {
        r->Render();
    }
    for (Rect* r : lane)
    {
        r->Render();
    }
    Judgeline->Render();
    for (Note* r : note)
    {
        if (r->GetLoading()) {
            r->Render();
        }
    }
    for (TextureRect* r : judge0)
    {
        if (r->GetLoading()) {
            r->Render();
        }
    }
    for (TextureRect* r : judge1)
    {
        if (r->GetLoading()) {
            r->Render();
        }
    }
}

void RhythmGame::PostRender()
{
}

void RhythmGame::GUI()
{
}
