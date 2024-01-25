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

int main() {
	//����: �ڷḦ ��� �ڷᱸ��
	//vector<���� �ڷ���> �����̸�;���� ������ �Ѵ�.
	vector<int> vecInt;

	vecInt.push_back(3);
	vecInt.push_back(2);
	vecInt.push_back(4);
	vecInt.push_back(7);

	// 3 2 4 7
	
	// ���� ���ͷ�����: ������ �ּҰ��� �ӽ÷� ���� ����
	vector<int>::iterator iter;

	for (iter = vecInt.begin(); iter!=vecInt.end(); iter++)
	{
		cout << (*iter) << endl;
	}

	return 0;
}