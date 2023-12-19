#include "stdafx.h"

/*
하이로우세븐
52장의 포커카드 사용
게임시작 후 5장의 카드를 오픈해서 보여줌
그 다음 1장이 7보다, 작다, 같다를 맞히는 게임
42장이 소모되었을 때, 카드를 셔플함.
*/

enum E_SHAPE { E_SPADE, E_DIA, E_HEART, E_CLOVER, E_MAX};
enum E_SELECT { E_QUIT, E_HIGH, E_LOW, E_SEVEN};

struct tagCards {
    string strShape;
    int nNumber;
};

void InitCards(tagCards* cards);
void SuffleCards(tagCards* cards);
void PrintAllCards(tagCards* cards);
void PrintCards(tagCards* cards, int nIndex);

int Betting(int money);
void PrintOneCard(tagCards* cards, int nIndex);
int main()
{
    srand(time(NULL));
    rand();

    tagCards stCards[52];
    int nIndex = 0;
    int nMymoney = 10000;
    bool isPlaying = true;

    InitCards(stCards);
    SuffleCards(stCards);
    PrintAllCards(stCards);

    system("pause");    

    while (isPlaying) {
        system("cls");


        if (nMymoney < 100) {
            cout << "베팅할 금액이 없습니다. 게임을 종료합니다." << endl;
            isPlaying = false;
        }
        else if (nIndex >= 42) {
            SuffleCards(stCards);
            cout << "새 카드로 게임을 계속합니다." << endl;
            nIndex = 0;
            system("pause");
        }
        else {
            int nSelect = -1;
            E_SELECT eSelect;
            int nBet;

            PrintCards(stCards, nIndex);
            while (nSelect <0 || 3<nSelect) 
            {
                
                cout << "현재 금액 : " << nMymoney << endl;
                cout << "1.하이 2.로우 3.세븐 (0.종료)";
                cin >> nSelect;
            }
            
            eSelect = (E_SELECT)nSelect;

            switch (eSelect)
            {
            case E_QUIT:
                cout << "게임을 종료합니다." << endl;
                isPlaying = false;
                break;
            case E_HIGH:
                nBet= Betting(nMymoney);
                if (stCards[nIndex+5].nNumber>7) {
                    cout << "베팅 성공! : ";
                    nMymoney += nBet;
                }
                else {
                    cout << "베팅 실패! : ";
                    nMymoney -= nBet;
                }
                PrintOneCard(stCards, nIndex + 5);
                break;
            case E_LOW:
                nBet= Betting(nMymoney);
                if (stCards[nIndex + 5].nNumber < 7) {
                    cout << "베팅 성공! : ";
                    nMymoney += nBet;
                }
                else {
                    cout << "베팅 실패! : ";
                    nMymoney -= nBet;
                }
                PrintOneCard(stCards, nIndex + 5);
                break;
            case E_SEVEN:
                nBet = Betting(nMymoney);
                if (stCards[nIndex + 5].nNumber == 7) {
                    cout << "베팅 성공! : ";
                    nMymoney += (nBet*2);
                }
                else {
                    cout << "베팅 실패! : ";
                    nMymoney -= nBet;
                }
                PrintOneCard(stCards, nIndex + 5);
                break;
            }

            nIndex += 6;

            Sleep(2000);
        }
    }
    system("pause");
    return 0;
}


void InitCards(tagCards* cards) {
    for (E_SHAPE i = E_SPADE; i < E_MAX; i = (E_SHAPE)(i + 1)) {
        for (int j = 0; j < 13; j++)
        {
            //카드의 문자 선언
            switch (i)
            {
            case E_SPADE:
                cards[i * 13 + j].strShape = "♠";
                break;
            case E_DIA:
                cards[i * 13 + j].strShape = "◆";
                break;
            case E_HEART:
                cards[i * 13 + j].strShape = "♥";
                break;
            case E_CLOVER:
                cards[i * 13 + j].strShape = "♣";
                break;
            }
            //카드의 숫자 선언
            cards[i * 13 + j].nNumber = j + 1;
        }
    }
}
void SuffleCards(tagCards* cards) {
    for (int i = 0; i < 1000; i++)
    {
        int nSrc = rand() % 52;
        int nDest = rand() % 52;

        tagCards stTemp = cards[nSrc];
        cards[nSrc] = cards[nDest];
        cards[nDest] = stTemp;
    }
}
void PrintAllCards(tagCards* cards) {
    for (int i = 0; i < 52; i++)
    {
        cout << cards[i].strShape;
        switch (cards[i].nNumber)
        {
        case 1:
            cout << 'A';
            break;
        case 11:
            cout << 'J';
            break;
        case 12:
            cout << 'Q';
            break;
        case 13:
            cout << 'K';
            break;
        default:
            cout << cards[i].nNumber;
            break;
        }
        cout << "\t";

        if (i % 13 == 12) {
            cout << endl;
        }
    }
}
void PrintCards(tagCards* cards, int nIndex) {
    for (int i = nIndex; i < (nIndex+5); i++)
    {
        cout << cards[i].strShape;
        switch (cards[i].nNumber)
        {
        case 1:
            cout << 'A';
            break;
        case 11:
            cout << 'J';
            break;
        case 12:
            cout << 'Q';
            break;
        case 13:
            cout << 'K';
            break;
        default:
            cout << cards[i].nNumber;
            break;
        }
        cout << "\t";
    }
    cout << "\t ( ? )\t" << endl;
}
int Betting(int money) {
    int nBet = 0;
    while (nBet < 100 || money < nBet) {
        cout << "베팅할 금액을 입력해 주세요.";
        cin >> nBet;
    }
    return nBet;
}
void PrintOneCard(tagCards* cards, int nIndex) {
    cout << cards[nIndex].strShape;
    switch (cards[nIndex].nNumber)
    {
    case 1:
        cout << 'A';
        break;
    case 11:
        cout << 'J';
        break;
    case 12:
        cout << 'Q';
        break;
    case 13:
        cout << 'K';
        break;
    default:
        cout << cards[nIndex].nNumber;
        break;
    }
}