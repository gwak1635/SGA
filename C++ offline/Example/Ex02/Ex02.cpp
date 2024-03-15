#include "Ex02.h"

void Ex02()
{
    {   // 기본적으로 모든 문자를 1Byte 크기로 받아옴
        // 그러다 보니 한글이나 일부 특수문자는 입,출력이 힘듬
        char astring[100];
        string cString = "";
    }

    // wstring은 문자를 사용할때 L을 붙여줘야하는 번거로움이 크지만
    // 모든 문자를 2Byte 크기로 받아오기 때문에
    // 한글이나 특수문자 같은 무거운 문자를 
    // 안정적으로 사용할수 있다.
    wstring wString = L"";

    string temp = "";

    cout << "문자를 입력해 주세요 : ";
    wcin >> wString;

    wcout << wString;

    // wstring과 stringd에 들어있는 문자열과
    // 우리가 사용할 문자열을 비교하기 위해서는
    // 해당 기능들 안에 들어있는 compare함수를 이용해 줘야한다.
    if (wString.compare(L"남쪽사냥터") || wString.compare(L"안녕"))
    {
        cout << " 반갑습니다" << endl;
    }

}
