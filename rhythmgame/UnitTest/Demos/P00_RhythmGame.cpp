#include "stdafx.h"
#include "P00_RhythmGame.h"

//��Ʈ�� '���'�� ������ �� ���� �Ҹ���?
//���� ������� ���� ä�� ������ ������ ����� ����!
//��Ʈ�� ó���ǰų� ������ �̽� ���� �ؿ� ������ ��� ���쵵�� ����?

void RhythmGame::Init()
{
    int lanethick = 15;    
    //���� 3��(���� 2��) �����
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
    //���������� ��ǥ: 100
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
            //react ����
            cout << "React" << endl;
            Anote->SetLoading(false);
        }
        else {
            //��� ����
            cout << "Stray" << endl;
            Anote->SetLoading(false);
        }

    }



    for (Note* r : note)
    {
        if (r->GetLoading()) {
            r->NoteFall(baesok);
                        
            //��ĵ�ؼ� '���� ����' �� �ؿ� �ִ� ��Ʈ�� ã�� ��
            if (r->GetPosition().y < 100 - (155 * baesok * 0.120))
            {
                r->SetLoading(false);
            }
                //��Ʈ ���� �� �̽� ó��

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
