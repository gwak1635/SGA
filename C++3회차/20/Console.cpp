// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

enum E_SHAPE { E_SPADE, E_DIA, E_HEART, E_CLOVER, E_MAX};
enum E_SELECT { E_QUIT, E_HIGH, E_LOW, E_SEVEN };

//하이로우세븐
// 52장의 포커카드 사용
// 5장의 카드를 오픈
// 다음 1장이 7보다 크다, 작다, 같다를 맞추는 게임.
// 42장 사용 시 셔플

struct tagCard {
    char* szShape;
    int  nNumber;
};

void InitCards(tagCard* cards); //전체 카드 초기화, 배열의 변수값 유도!
void SuffleCards(tagCard* cards);
void PrintCards(tagCard* cards);
void PrintCards(tagCard* cards, int index);

void Play(tagCard* cards, int* money, int* index, bool* playing);
int Betting(int money);

int main()
{
    srand(time(NULL));
    rand();

    tagCard stCards[52];
    bool    isPlaying = true;
    int     nMyMoney = 10000;
    int     nCurrIndex = 5;

    InitCards(stCards);
    SuffleCards(stCards);
    PrintCards(stCards);

    system("pause");

    while (isPlaying)
    {
        system("cls");

        PrintCards(stCards, nCurrIndex);

        if (nMyMoney < 100)
        {
            cout << "더 이상 베팅할 금액이 없습니다. 게임을 종료합니다." << endl;
            isPlaying = false;
        }
        else if (nCurrIndex > 42) //새 카드로 교체(다시 섞기)
        {
            SuffleCards(stCards);
            nCurrIndex = 5;
            cout << "새 카드로 게임을 다시 시작합니다." << endl;
            system("pause");
        }
        else
        {
            Play(stCards, &nMyMoney, &nCurrIndex, &isPlaying);
            Sleep(2000);
        }
    }
    system("pause");

    return 0;
}

void InitCards(tagCard* cards) {
    for (E_SHAPE i = E_SPADE; i < E_MAX; i = (E_SHAPE)(i + 1))
    {
        for (int j = 0; j < 13; j++)
        {
            switch (i)
            {
            case E_SPADE:
                cards[i * 13 + j].szShape = (char*)"♠";
                break;
            case E_DIA:
                cards[i * 13 + j].szShape = (char*)"◆";
                break;
            case E_HEART:
                cards[i * 13 + j].szShape = (char*)"♥";
                break;
            case E_CLOVER:
                cards[i * 13 + j].szShape = (char*)"♣";
                break;
            }

            cards[i * 13 + j].nNumber = j + 1;
        }

    }
}
void SuffleCards(tagCard* cards) {

    for (int i = 0; i < 2600; i++)
    {
        int nSrc = rand() % 52;
        int nDest = rand() % 52;

        tagCard stTemp = cards[nSrc];
        cards[nSrc] = cards[nDest];
        cards[nDest] = stTemp;
    }

}
void PrintCards(tagCard* cards) {
    for (int i = 0; i < 52; i++)
    {
        switch (cards[i].nNumber)
        {
        case 1:
            cout << cards[i].szShape << "A" << "\t";
            break;
        case 11:
            cout << cards[i].szShape << "J" << "\t";
            break;
        case 12:
            cout << cards[i].szShape << "Q" << "\t";
            break;
        case 13:
            cout << cards[i].szShape << "K" << "\t";
            break;
        default:
            cout << cards[i].szShape << cards[i].nNumber << "\t";
            break;
        }
        if (i % 13 == 12)
            cout << endl;
    }
}

void PrintCards(tagCard* cards, int index) {
    for (int i = index-5; i < index; i++)
    {
        switch (cards[i].nNumber)
        {
        case 1:
            cout << cards[i].szShape << "A" << "\t";
            break;
        case 11:
            cout << cards[i].szShape << "J" << "\t";
            break;
        case 12:
            cout << cards[i].szShape << "Q" << "\t";
            break;
        case 13:
            cout << cards[i].szShape << "K" << "\t";
            break;
        default:
            cout << cards[i].szShape << cards[i].nNumber << "\t";
            break;
        }
    }
    cout << "\t ( ? )" << endl;
}

void Play(tagCard* cards, int* money, int* index, bool* playing) {
    int nSelect;
    E_SELECT eSelect;
    int nBet;

    cout << "현재 금액 : " << *money << endl;
    cout << "1.하이 2.로우 3.세븐 (0.종료) : ";
    cin >> nSelect;

    eSelect = (E_SELECT)nSelect;

    switch (eSelect)
    {
    case E_QUIT:
        cout << "게임을 종료합니다." << endl;
        *playing = false;
        break;
    case E_HIGH:
        nBet = Betting(*money);
        if (cards[*index].nNumber > 7) {
            cout << "베팅 성공 ! : ";
            *money += nBet;
        }
        else {
            cout << "베팅 실패 ! : "; 
            *money -= nBet;
        }
        cout << cards[*index].szShape << cards[*index].nNumber << endl;
        
        break;
    case E_LOW:
        nBet = Betting(*money);
        if (cards[*index].nNumber < 7) {
            cout << "베팅 성공 ! : ";
            *money += nBet;
        }
        else {
            cout << "베팅 실패 ! : ";
            *money -= nBet;
        }
        cout << cards[*index].szShape << cards[*index].nNumber << endl;
        
        break;
    case E_SEVEN:
        nBet = Betting(*money);
        if (cards[*index].nNumber == 7) {
            cout << "베팅 성공 ! : ";
            *money += nBet*2;
        }
        else {
            cout << "베팅 실패 ! : ";
            *money -= nBet;
        }
        cout << cards[*index].szShape << cards[*index].nNumber << endl;
        break;
    default:
        break;
    }

    *index += 6;
}
int Betting(int money) {
    int nBet = 0;

    while (nBet < 100 || money < nBet) {
        cout << "금액을 베팅하시오.(100~보유금액) : ";
        cin >> nBet;
    }

    return nBet;
}