#include<iostream>
#include<vector>

using namespace std;

/*
push_back(���ڰ�) : ���Ϳ� �ڷḦ �ִ´�. ���� ���ʿ�
pop_back() : ������ ������ �ڷḦ �����.
size() : ������ �� �ִ� �ڷ��� ������ ��ȯ�Ѵ�.
begin(): ������ ù��° ���� �ּҰ�
ex) begin()+3: ������ ù��° �����κ��� 3ĭ ���� �ּҰ�(4��° ���� �ּҰ�)
end(): ������ ������ ���� ���� �ּҰ�
insert(�ڷḦ ���� ��ġ �ּҰ�, ���� ��): Ư�� ��ġ�� ���� �ִ´�.
insert(�ڷḦ ���� ��ġ �ּҰ�, ����, ���� ��) : Ư�� ��ġ�� ���� ������ŭ ���� �ִ´�.
erase(�ڷḦ ���� ��ġ �ּҰ�):Ư�� ��ġ�� ���� �����.
clear(): ���� ��ü�� �����.
empty() : ���Ͱ� ����ִ��� Ȯ��
*/

struct Car {
	struct engine {
		int test;
	};
};

int main() {
	Car::engine a;
	a.test = 100;
	//����: �ڷḦ ��� �ڷᱸ��
	//vector<���� �ڷ���> �����̸�;���� ������ �Ѵ�.
	vector<int> vecInt;

	vecInt.push_back(3);
	vecInt.push_back(2);
	vecInt.push_back(7);
	vecInt.push_back(6);

	vecInt.insert(vecInt.end()-2, 5);
	
	//cout << vecInt[-1] << endl;
	//���̽� ����Ʈó���� �ȵȴ�!
	// 
	// ���� ���ͷ�����: ������ �ּҰ��� �ӽ÷� ���� ����
	vector<int>::iterator iter;//���� Ŭ���� ���� �ǰ�?

	for (iter = vecInt.begin(); iter!=vecInt.end(); iter++)
	{
		cout << (*iter) << endl;
	}

	return 0;
}

