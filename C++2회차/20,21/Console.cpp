// Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"

enum E_SHAPE {E_SPADE, E_DIA, E_HEART, E_CLOVER, E_MAX};
enum E_SELECT { E_QUIT, E_HIGH, E_LOW, E_SEVEN };

/*
하이로우세븐
52장의 포커카드 사용
게임시작 후 5장의 카드를 오픈해서 보여줌
그 다음 1장이 7보다, 작다, 같다를 맞히는 게임
42장이 소모되었을 때, 카드를 셔플함.
*/

struct tagCard {
    char* szShape;//특수문자이기 때문에 문자열로.
    int nNumber;
};

void InitCards(tagCard* cards); //전체 카드 초기화
void Suffle(tagCard* cards); // 카드 셔플
void Print(tagCard* cards); //카드 출력하기
void Print(tagCard* cards, int index); //플레이 카드 출력하기

void Play(tagCard* cards, int* money, int* index, bool* playing);
int Betting(int money);

int main()
{
    srand(time(NULL));
    rand();

    tagCard stCards[52];
    bool    isPlaying = true;
    int     nMyMoney = 10000;
    int     nCurrIndex = 5;//카드 6개를 확인하기 때문에

    InitCards(stCards);//배열의 주소(포인터)가 들어감
    Suffle(stCards);
    Print(stCards);

    system("pause");

    while (isPlaying) {
        system("cls");

        Print(stCards, nCurrIndex);

        if (nMyMoney < 100) {
            //게임 강제종료(돈없)
            cout << "진행 가능한 돈이 없습니다. 게임을 종료합니다." << endl;
            isPlaying = false;
        }
        else if(nCurrIndex>42) {
            Suffle(stCards);
            nCurrIndex = 5;

            cout << " 새 카드로 게임을 계속합니다." << endl;

            system("pause");
        }
        else {
            Play(stCards, &nMyMoney, &nCurrIndex, &isPlaying);
        }
    }
    
   
    system("pause");

    return 0;
}

void InitCards(tagCard* cards)
{
    for (E_SHAPE i = E_SPADE; i < E_MAX; i= (E_SHAPE)(i + 1))//ENUM문으로 강제 형변환 해주어야 함.
    {
        for (int j = 0; j < 13 ; j++)
        {
            //카드의 문자 선언
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
            default:
                break;
            }

            //카드의 숫자 선언
            cards[i * 13 + j].nNumber = j + 1;
        }
    }
}

void Suffle(tagCard* cards)
{
    for (int i = 0; i < 1000; i++)
    {
        int nSrc = rand() % 52;
        int nDest = rand() % 52;

        tagCard stTemp = cards[nSrc];
        cards[nSrc] = cards[nDest];
        cards[nDest] = stTemp;
    }
}

void Print(tagCard* cards)
{
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

void Print(tagCard* cards, int index) {
    //인데스 번호가 5부터 시작하니까 index-5 == 0부터 시작하기
    //index=5이브로 arr[4]까지만 출력하게끔 함.
    for (int i = index - 5; i < index; i++)
    {
        if (cards[i].nNumber == 1) {
            cout << cards[i].szShape << "A" << "\t";
        }
        else if(cards[i].nNumber == 11) {
            cout << cards[i].szShape << "J" << "\t";
        }
        else if (cards[i].nNumber == 12) {
            cout << cards[i].szShape << "Q" << "\t";
        }
        else if (cards[i].nNumber == 13) {
            cout << cards[i].szShape << "K" << "\t";
        }
        else {
            cout << cards[i].szShape << cards[i].nNumber << "\t";
        }
    }
    cout << "\t ( ? )\t" << endl;
}

void Play(tagCard* cards, int* money, int* index, bool* playing) 
{
    int         nSelect;
    E_SELECT    eSelect;
    int         nBet;

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
        nBet = Betting(*money);// 금액 베팅

        if (cards[*index].nNumber > 7)//승
        {
            cout << "베팅 성공! : ";
            *money += nBet;
        }
        else //패
        {
            cout << "베팅 실패! : ";
            *money -= nBet;
        }
        cout << cards[*index].szShape << cards[*index].nNumber << endl;
        break;
    case E_LOW:
        nBet = Betting(*money);// 금액 베팅

        if (cards[*index].nNumber < 7)//승
        {
            cout << "베팅 성공! : ";
            *money += nBet;
        }
        else //패
        {
            cout << "베팅 실패! : ";
            *money -= nBet;
        }
        cout << cards[*index].szShape << cards[*index].nNumber << endl;
        break;
    case E_SEVEN:
        nBet = Betting(*money);// 금액 베팅

        if (cards[*index].nNumber == 7)//승
        {
            cout << "베팅 성공! : ";
            *money += nBet * 2;
        }
        else //패
        {
            cout << "베팅 실패! : ";
            *money -= nBet;
        }
        cout << cards[*index].szShape << cards[*index].nNumber << endl;
        break;
    default:
        break;
    }

    *index += 6;

    Sleep(2000);
}
int Betting(int money) {
    int nBet = 0;

    while (nBet < 100 || money < nBet)//정상적인 베팅이 될 때까지 무한반복
    {
        cout << "금액을 베팅하시오.(100~보유금액) : ";
        cin >> nBet;
    }
    return nBet;
}