#include<iostream>
#include<vector>

using namespace std;

/*
push_back(인자값) : 벡터에 자료를 넣는다. 제일 뒷쪽에
pop_back() : 벡터의 마지막 자료를 지운다.
size() : 벡터의 들어가 있는 자료의 갯수를 반환한다.
begin(): 벡터의 첫번째 값의 주소값
ex) begin()+3: 벡터의 첫번째 값으로부터 3칸 뒤의 주소값(4번째 값의 주소값)
end(): 벡터의 마지막 값의 다음 주소값
insert(자료를 넣을 위치 주소값, 넣을 값): 특정 위치에 값을 넣는다.
insert(자료를 넣을 위치 주소값, 개수, 넣을 값) : 특정 위치에 지정 갯수만큼 값을 넣는다.
erase(자료를 지울 위치 주소값):특정 위치의 값을 지운다.
clear(): 벡터 전체를 지운다.
empty() : 벡터가 비어있는지 확인
*/

struct Car {
	struct engine {
		int test;
	};
};

int main() {
	Car::engine a;
	a.test = 100;
	//벡터: 자료를 담는 자료구조
	//vector<담을 자료형> 변수이름;으로 선언을 한다.
	vector<int> vecInt;

	vecInt.push_back(3);
	vecInt.push_back(2);
	vecInt.push_back(7);
	vecInt.push_back(6);

	vecInt.insert(vecInt.end()-2, 5);
	
	//cout << vecInt[-1] << endl;
	//파이썬 리스트처럼은 안된다!
	// 
	// 벡터 이터레이터: 벡터의 주소값을 임시로 담을 변수
	vector<int>::iterator iter;//이중 클래스 같은 건가?

	for (iter = vecInt.begin(); iter!=vecInt.end(); iter++)
	{
		cout << (*iter) << endl;
	}

	return 0;
}

