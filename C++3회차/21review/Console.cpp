#include "stdafx.h"

//하이로우세븐
// 52장의 포커카드 사용
// 5장의 카드를 오픈
// 다음 1장이 7보다 크다, 작다, 같다를 맞추는 게임.
// 42장 사용 시 셔플

struct tagCard {
    char*  szShape;
    int    nNumber;
};

enum E_SHAPE { E_SPADE, E_DIA, E_HEART, E_CLOVER, E_MAX };
enum E_SELECT { E_QUIT, E_HIGH, E_LOW, E_SEVEN };

void InitCards(tagCard* cards);
void suffleCards(tagCard* cards);
void PrintCards(tagCard* cards);
void PrintCards(tagCard* cards, int index);
int Bet(int money);

int main()
{
    srand(time(NULL));
    rand();

    //플레이 관련 변수
    int nMoney = 10000;
    bool isPlaying = true;
    int nCurrIndex = 5;

    //백지 카드 52장 생성
    tagCard stCard[52];

    //카드를 초기화, 셔플
    InitCards(stCard);
    suffleCards(stCard);

    //카드를 확인하는 함수와 일시정지(디버그용)
    PrintCards(stCard);
    system("pause");

    while (isPlaying) {
        if (nMoney<100)
        {
            cout << "금액이 부족합니다. 게임을 종료합니다." << endl;
            isPlaying = false;
        }
        else if (nCurrIndex > 42) {
            suffleCards(stCard);
            nCurrIndex = 5;
            cout << "새 카드로 게임을 계속합니다." << endl;
            system("pause");
        }
        else {
            int nSelect;
            E_SELECT eSelect;
            int nBet;
            system("cls");
            PrintCards(stCard, nCurrIndex);
            cout << "현재 금액 : " << nMoney << endl;
            cout << "1.하이 2.로우 3.세븐 (0.게임 종료) : ";
               
            //선택지를 고르고 enum문으로 변환
            cin >> nSelect;
            eSelect = (E_SELECT)nSelect;

            switch (eSelect)
            {
            case E_QUIT:
                cout << "게임을 종료합니다." << endl;
                isPlaying = false;
                break;
            case E_HIGH:
                nBet = Bet(nMoney);
                if (stCard[nCurrIndex].nNumber > 7) {
                    cout << "배팅 성공! : ";
                    nMoney += nBet;
                }
                else {
                    cout << "배팅 실패! : ";
                    nMoney -= nBet;
                }
                cout << stCard[nCurrIndex].szShape << stCard[nCurrIndex].nNumber << endl;
                break;
            case E_LOW:
                nBet = Bet(nMoney);
                if (stCard[nCurrIndex].nNumber < 7) {
                    cout << "배팅 성공! : ";
                    nMoney += nBet;
                }
                else {
                    cout << "배팅 실패! : ";
                    nMoney -= nBet;
                }
                cout << stCard[nCurrIndex].szShape << stCard[nCurrIndex].nNumber << endl;
                break;
            case E_SEVEN:
                nBet = Bet(nMoney);
                if (stCard[nCurrIndex].nNumber == 7) {
                    cout << "배팅 성공! : ";
                    nMoney += nBet;
                }
                else {
                    cout << "배팅 실패! : ";
                    nMoney -= nBet;
                }
                cout << stCard[nCurrIndex].szShape << stCard[nCurrIndex].nNumber << endl;
                break;
            }

            nCurrIndex += 6;
            Sleep(2000);

        }
    }

    system("pause");
    return 0;
}

void InitCards(tagCard* cards) {
    for (E_SHAPE i = E_SPADE; i < E_MAX; i=(E_SHAPE)(i+1))
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

            cards[i * 13 + j].nNumber = j+1;
        }
    }
}
void suffleCards(tagCard* cards) {
    for (int i = 0; i < 2600; i++)
    {
        int nSrc = rand() % 52;
        int nDest = rand() % 52;

        tagCard stTemp = cards[nSrc];
        cards[nSrc] = cards[nDest];
        cards[nDest] = stTemp;

    }
}
void PrintCards(tagCard* cards){
    for (int i = 0; i < 52; i++)
    {
        switch (cards[i].nNumber)
        {
        case 1:
            cout << cards[i].szShape << "A\t";
            break;
        case 11:
            cout << cards[i].szShape << "J\t";
            break;
        case 12:
            cout << cards[i].szShape << "Q\t";
            break;
        case 13:
            cout << cards[i].szShape << "K\t";
            break;
        default:
            cout << cards[i].szShape << cards[i].nNumber <<"\t";
            break;
        }
        if (i % 13 == 12) {
            cout << endl;
        }
    }
}
void PrintCards(tagCard* cards, int index) {
    for (int i = index-5; i < index; i++)
    {
        switch (cards[i].nNumber)
        {
        case 1:
            cout << cards[i].szShape << "A\t";
            break;
        case 11:
            cout << cards[i].szShape << "J\t";
            break;
        case 12:
            cout << cards[i].szShape << "Q\t";
            break;
        case 13:
            cout << cards[i].szShape << "K\t";
            break;
        default:
            cout << cards[i].szShape << cards[i].nNumber << "\t";
            break;
        }
    }

    cout << "( ? )" << endl;
}
int Bet(int money) {
    int nBetmoney=0;
    while (nBetmoney < 100 || money < nBetmoney )
    {
        cout << "금액을 베팅하시오(100~소지금) : ";
        cin >> nBetmoney;
    }
    return nBetmoney;
}