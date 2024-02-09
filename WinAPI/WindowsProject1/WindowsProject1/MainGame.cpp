#include "framework.h"
#include "MainGame.h"

// OOP (Object Oriented Programming : 객체 지향 프로그래밍)
// High Cohesion, Low Copupling(높은 응집도, 낲은 결합도)


MainGame::MainGame()
{
    m_pPlayer = new Player;
    m_pObjects = new Objects;
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{

	m_nScore = 0;
	m_nLevel = 1;

    if (m_pPlayer) m_pPlayer->Init();
    if (m_pObjects) m_pObjects->Init();
}

void MainGame::Update()
{
    InvalidateRect(g_hWnd, NULL, true);
       
    m_nLevel = m_nScore / 100 + 1;
    // 레벨 정보를 오브젝트에 넘겨줘야 한다.
    if (m_pObjects) m_pObjects->SetLevel(m_nLevel);

    if (m_pPlayer)  m_pPlayer->Update();
    if (m_pObjects) m_pObjects->Update();

    vector<tagBox>::iterator iter;

    for (iter = m_pObjects->GetBox().begin(); iter != m_pObjects->GetBox().end(); iter++)
    {

        RECT rt;
        RECT rtIter = iter->rt;

        if (iter->rt.top > WINSIZEY)//변수가 아니라 이터레이터라서 이짓을 해야함
        {
            m_nScore++;
        }
        else if (IntersectRect(&rt, &m_pPlayer->GetRect(), &rtIter)) {
            m_nScore -= 10;
            m_pObjects->GetBox().erase(iter);
            break;
        }
        else if (PtInRect(&rtIter, g_ptMouse)) {
            m_nScore += 5;
            m_pObjects->GetBox().erase(iter);
            break;
        }

    }
}

void MainGame::Render()
{
    PAINTSTRUCT ps;

    HDC g_hDC = BeginPaint(g_hWnd, &ps);

    if (m_pPlayer)  m_pPlayer->Render();
    if (m_pObjects) m_pObjects->Render();

    char szBuf[32];

    _itoa_s(m_nLevel, szBuf, 10);     //정수를 문자열로 바꾸는 함수!
    string str = string(szBuf);
    TextOutA(g_hDC, 10, 10, str.c_str(), str.length());

    _itoa_s(m_nScore, szBuf, 10); 
    str = string(szBuf);
    TextOutA(g_hDC, 10, 30, str.c_str(), str.length());

    EndPaint(g_hWnd, &ps);
}
