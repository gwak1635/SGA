#pragma once

template <typename T>
class BTree {

public:
	BTree(){

	}
	~BTree(){
		DestroyTree(root);
	}

	struct Node
	{
		T Data;
		Node* Left;
		Node* Right;
	};

	void PreOrder(Node* node) {
		if (node == NULL) return;

		cout << ' ' << node->Data;
		PreOrder(node->Left);
		PreOrder(node->Right);
	}

	void InOrder(Node* node) {
		if (node == NULL) return;

		InOrder(node->Left);
		cout << ' ' << node->Data;
		InOrder(node->Right);
	}

	void PostOrder(Node* node) {
		if (node == NULL) return;

		PostOrder(node->Left);
		PostOrder(node->Right);
		cout << ' ' << node->Data;
	}

	void Root(Node* node) { root = node; }

	//객체 생성 없이 노드를 만들고 지우기 위해 정적 함수로 만듦
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->Left = node->Right = NULL;

		return node;
	}

	static void Destroy(Node* node)
	{
		delete node;
		node = NULL;
	}

	
private:
	Node* root;

	void DestroyTree(Node* node) { //전위 순회
		if (node == NULL) return;

		Destroy(node->Left);
		Destroy(node->Right);

		Destroy(node);
	}
	
};