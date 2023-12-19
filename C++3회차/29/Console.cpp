#include "stdafx.h"

/*
push_back(인자): 벡터의 맨 끝에 자료를 넣는다.
pop.back() :벡터의 마지막 자료를 지운다.(반환X)
size() : 벡터에 들어가 있는 자료의 갯수를 반환한다.
begin() : 벡터의 첫번째 값의 주소값을 반환한다.[포인터 접근 필요]
ex) begin() + 3 : 벡터의 네 번째 값의 주소
end() : 벡터의 마지막 값의 다음 주소값 [end()-n]?
insert(자료를 넣을 위치 주소값, 넣을 값) : 특정 위치에 값을 넣는다.[연결 리스트인가?]
insert(자료를 넣을 위치 주소값, 갯수, 넣을 값) : 특정 위치에 지정 갯수만큼 값을 넣는다.
erase(자료를 지울 위치 주소값) : 특정 위치의 값을 지운다.
clear() : 벡터 전체를 지운다.
bool empty() : 벡터가 비어있는지 확인
*/

int main()
{
    //벡터: 자료구조의 일종
    //vector<자료형> 변수명
    vector<int> vecInt;//구조체, 클래스도 들어갈 수 있음.

    //cout << vecInt.empty() << endl; //true(1)

    vecInt.push_back(3);
    vecInt.push_back(2);
    vecInt.push_back(4);
    vecInt.push_back(7);

    //cout << vecInt.empty() << endl; //false(0)

    //이터...뭐요?이터레이터? 반복자?
    //벡터의 주소값을 임시로 담을 변수
    //데이터를 끼워넣을때 편리핳ㅁ
    /*vector<int>::iterator iter;
    for (iter = vecInt.begin();iter != vecInt.end();iter++)
    {
        cout << (*iter) << endl;
    }*/

    //cout << *(vecInt.begin() + 3) << endl;
    //cout << *(vecInt.end()-1) << endl;

    // vecInt[3] => *(vecInt.begin() +3)

    vecInt.insert(vecInt.begin() + 2, 10);
    vecInt.insert(vecInt.begin() + 2, 3, 5 ); // 3 2 5 5 5 10 4 7 

    //인덱스로 벡터에 접근하는 방식
    for (int i = 0; i < vecInt.size(); i++)
    {
        cout << vecInt[i] << endl;
    }

    cout << endl;

    vecInt.clear();

    cout << vecInt.empty() << endl;

    system("pause");


    return 0;
}
