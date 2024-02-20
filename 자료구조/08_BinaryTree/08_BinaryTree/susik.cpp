//후위 표기 수식을 우->좌 읽기
//오른쪽에 있는 연산자가 루트 노드
//바로 왼쪽에 있는 노드가 연산자라면 가지 노드, 그 뒤의 2개 토큰은 자식 노드(우,좌)
//그 2개 토큰 중 하나가 연산자라면 또 가지 노드
//토큰 2개가 모드 숫자라면 리프 노드

#include<iostream>
using namespace std;
#include"BinaryTree.h"

#include<string>

//(3*4)-(1+4)

//후위 순회로 처리된 값을 다시 이진 트리로 만들기
void Expression(const char* postfix, BTree<char>::Node** node){
	char* str = const_cast<char*>(postfix);
	//이거 혼나기 딱 좋은 짓! 수정 불가능한 걸 임의로 깨려고 해? 喝!!!
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

//전위와 후위를 혼종한 순회를 통해 노드 값 계산하기
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