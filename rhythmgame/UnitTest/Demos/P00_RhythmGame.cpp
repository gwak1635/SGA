#include "stdafx.h"
#include "P00_RhythmGame.h"

//게이지를 만들어야 한다
//파일 입출력을 통해 채보 데이터 파일을 만들어 보자!

void RhythmGame::Init()
{
    int lanethick = 15;    
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
    
    note.push_back(new Note({ WinMaxWidth * 0.5f - 75 - lanethick / 2, 720, 0 },
        { 150.0f,30.0f,1 }, 0, 1)
    );
    note.push_back(new Note({ WinMaxWidth * 0.5f + 75 + lanethick / 2, 720+onesec*0.5f, 0 },
        { 150.0f,30.0f,1 }, 0, 2)
    );
    note.push_back(new Note({WinMaxWidth * 0.5f - 75 - lanethick / 2, 720 + onesec, 0},
        { 150.0f,30.0f,1 }, 0, 0)
    );
    note.push_back(new Note({ WinMaxWidth * 0.5f + 75 + lanethick / 2, 720 + onesec * 1.5f, 0 },
        { 150.0f,30.0f,1 }, 0, 3)
    );
    for (Note* r : note)
    {
        r->UpdateWorld();
    }

    {
        judge.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f, 500, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\hexed.png")
        );
        judge.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f, 500, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\react.png")
        );
        judge.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f, 500, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\stray.png")
        );
        judge.push_back(new TextureRect(
            Vector3(WinMaxWidth * 0.5f, 500, 0),
            Vector3(150, 50, 1), 0.0f, TexturePath + L"150p50\\miss.png")
        );
        for (TextureRect* r : judge)
        {
            r->UpdateWorld();
            r->SetLoading(false);
        }
    }
}

void RhythmGame::Destroy()
{
    for (TextureRect* r : judge)
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

void RhythmGame::SeeJudge(int j_judge) {
    for (TextureRect* r : judge)
    {
        r->SetLoading(false);
    }
    judge[j_judge]->SetLoading(true);
}

void RhythmGame::NoteJudge(int j_lane)
{
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
        cout << "Hexed" << endl;
        Anote->SetLoading(false);
        SeeJudge(0);

    }
    else if (100 - (onesec * 0.080) <= Anote->GetPosition().y && Anote->GetPosition().y <= 100 + (onesec * 0.080))
    {
        //react 판정
        cout << "React" << endl;
        SeeJudge(1);
    }
    else {
        //배드 판정
        cout << "Stray" << endl;
        SeeJudge(2);
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
    

    for (TextureRect* r : judge)
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
            if (r->GetPosition().y < 100 - (155 * baesok * 0.120))
            {
                r->SetLoading(false);
                SeeJudge(3);
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
    for (TextureRect* r : judge)
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
