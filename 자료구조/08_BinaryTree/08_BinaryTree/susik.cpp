//���� ǥ�� ������ ��->�� �б�
//�����ʿ� �ִ� �����ڰ� ��Ʈ ���
//�ٷ� ���ʿ� �ִ� ��尡 �����ڶ�� ���� ���, �� ���� 2�� ��ū�� �ڽ� ���(��,��)
//�� 2�� ��ū �� �ϳ��� �����ڶ�� �� ���� ���
//��ū 2���� ��� ���ڶ�� ���� ���

#include<iostream>
using namespace std;
#include"BinaryTree.h"

#include<string>

//(3*4)-(1+4)

//���� ��ȸ�� ó���� ���� �ٽ� ���� Ʈ���� �����
void Expression(const char* postfix, BTree<char>::Node** node){
	char* str = const_cast<char*>(postfix);
	//�̰� ȥ���� �� ���� ��! ���� �Ұ����� �� ���Ƿ� ������ ��? ��!!!
	size_t length = strlen(str);

	char token = str[length - 1];
	str[length - 1] = NULL;

	switch (token) 
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		{
			*node = BTree<char>::CreateNode(token);

			Expression(postfix, &(*node)->Right);
			Expression(postfix, &(*node)->Left);
		}
		break;
		default:
		{
			*node = BTree<char>::CreateNode(token);
		}
		break;
	}
}

//������ ������ ȥ���� ��ȸ�� ���� ��� �� ����ϱ�
int Evaluate(BTree<char>::Node* node) {
	if (node == NULL) return 0;

	if ('0' <= node->Data && node->Data <= '9')
	{
		char temp[4];
		memset(temp, 0, sizeof(temp));

		temp[0] = node->Data;
		return atoi(temp);
	}
	else {
		int left = Evaluate(node->Left);
		int right = Evaluate(node->Right);
		switch (node->Data)
		{
		case '+': return left + right;
		case '-':return left - right;
		case '*':return left * right;
		case '/':return left / right;
		case '%':return left % right;
		}
	}

	return 0;
}

void main() {
	string postfix = "34*14+-";

	BTree<char>::Node* root = NULL;
	Expression(postfix.c_str(), &root);


	BTree<char> tree;
	tree.Root(root);

	cout << "PreOrder" << endl;
	tree.InOrder(root);
	cout << endl << endl;

	cout << "PostOrder" << endl;
	tree.PostOrder(root);
	cout << endl << endl;

	cout << "Evaluate : "<<Evaluate(root) << endl;
}