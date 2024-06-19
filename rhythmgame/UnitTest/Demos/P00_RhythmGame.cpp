#include "stdafx.h"
#include "P00_RhythmGame.h"

//노트의 '노드'를 만들라는 건 무슨 소리지?
//파일 입출력을 통해 채보 데이터 파일을 만들어 보자!
//노트가 처리되거나 판정선 미스 범위 밑에 있으면 어떻게 지우도록 하지?

void RhythmGame::Init()
{
    int lanethick = 15;    
    //라인 3개(레인 2개) 만들기
    lane.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f-150-lanethick, WinMaxHeight * 0.5f, 0),
        Vector3(20, WinMaxHeight, 1), 0.0f)
    );
    lane.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0),
        Vector3(20, WinMaxHeight, 1), 0.0f)
    );
    lane.push_back(new Rect(
        Vector3(WinMaxWidth * 0.5f+150+ lanethick, WinMaxHeight * 0.5f, 0),
        Vector3(20, WinMaxHeight, 1), 0.0f)
    );
    for (Rect* r : lane)
    {
        r->SetColor(Color(0, 0, 0, 1));
        r->UpdateWorld();
    }
    //저지라인의 좌표: 100
    Judgeline=new Rect(
        Vector3(WinMaxWidth * 0.5f, 100, 0),
        Vector3(lanethick+300, lanethick, 1), 0.0f);

    Judgeline->SetColor(Color(1, 0, 0, 1));
    Judgeline->UpdateWorld();

    note.push_back(new Note({ WinMaxWidth * 0.5f - 75 - lanethick / 2, 720, 0 },
        { 150.0f,30.0f,1 }, 0, 2)
    );
    note.push_back(new Note({ WinMaxWidth * 0.5f + 75 + lanethick / 2, 875, 0 },
        { 150.0f,30.0f,1 }, 0, 3)
    );
    note.push_back(new Note({WinMaxWidth * 0.5f - 75 - lanethick / 2, 1030, 0},
        { 150.0f,30.0f,1 }, 0, 1)
    );
    note.push_back(new Note({ WinMaxWidth * 0.5f + 75 + lanethick / 2, 1185, 0 },
        { 150.0f,30.0f,1 }, 0, 4)
    );
    for (Note* r : note)
    {
        r->UpdateWorld();
    }
}

void RhythmGame::Destroy()
{
    for (TextureRect* r : note)
    {
        SAFE_DELETE(r);
    }
    SAFE_DELETE(Judgeline);
    for (Rect* r : lane)
    {
        SAFE_DELETE(r);
    }
    
}



void RhythmGame::Update()
{
    float onesec = 155 * baesok;



    if (Keyboard::Get()->Down('A')) {
        Note* Anote = nullptr;
        for (Note* r : note) {
            if (r->GetLoading()) {
                if (r->GetLane() == 1 && (100 - (onesec * 0.120) <= r->GetPosition().y && r->GetPosition().y <= 100 + (onesec * 0.120)))
                {
                    if (Anote == nullptr) { Anote = r;}
                    if (Anote->GetPosition().y > r->GetPosition().y) {Anote = r;}
                }
            }
        }
        if (Anote == nullptr) {}
        else if (100 - (onesec * 0.040) <= Anote->GetPosition().y && Anote->GetPosition().y <= 100 + (onesec * 0.040))
        {
            cout << "Hexed" << endl;
            Anote->SetLoading(false);

        }
        else if (100 - (onesec * 0.080) <= Anote->GetPosition().y && Anote->GetPosition().y <= 100 + (onesec * 0.080))
        {
            //react 판정
            cout << "React" << endl;
            Anote->SetLoading(false);
        }
        else {
            //배드 판정
            cout << "Stray" << endl;
            Anote->SetLoading(false);
        }

    }



    for (Note* r : note)
    {
        if (r->GetLoading()) {
            r->NoteFall(baesok);
                        
            //스캔해서 '판정 범위' 맨 밑에 있는 노트를 찾아 냄
            if (r->GetPosition().y < 100 - (155 * baesok * 0.120))
            {
                r->SetLoading(false);
            }
                //노트 삭제 후 미스 처리

            r->Update();
        }
    } 



    for (Rect* r : lane)
    {
        r->Update();
    }
    Judgeline->Update();
}

void RhythmGame::Render()
{
    for (Note* r : note)
    {
        if (r->GetLoading()) {
            r->Render();
        }
    }
    for (Rect* r : lane)
    {
        r->Render();
    }
    Judgeline->Render();
}

void RhythmGame::PostRender()
{
}

void RhythmGame::GUI()
{
}
