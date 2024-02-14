#include <stdio.h>
#include <stack>
using namespace std;

void main() {
	stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);

	while (s.empty() == false) {
		int top = s.top();//맨 위 가져오기
		printf("Top : %d\n", top);

		s.pop();//맨 위 제거
	}
}

//구현법: 배열, 연결리스트s