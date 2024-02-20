#pragma once
 
template<typename T> class Tree
{
public:
	struct Node;

public:
	void AddChild(Node* parent, Node* child) {
		if (parent->LeftChild == NULL) {
			parent->LeftChild = child;
		}
		else
		{
			Node* node = parent->LeftChild;
			while (node->RightSibiling != NULL) {
				node = node->RightSibiling;
			}
			node->RightSibiling = child;
		}
	}

	void PrintNode(Node* node, int depth) {
		for (int i = 0; i < depth; i++)
		{
				printf("-");
		}

		//if(depth!=0) //자식 노드만 출력하게 만들기
			printf("%c\n", node->Data);

		if (node->LeftChild != NULL)
			PrintNode(node->LeftChild, depth + 1);

		//if (depth != 0) { //자식 노드만 출력하게 만들기
			if (node->RightSibiling != NULL)
				PrintNode(node->RightSibiling, depth);

		//}
		
	}

	static Node* CreateNode(T data) {
		Node* node = new Node();
		node->Data = data;
		node->LeftChild = node->RightSibiling = NULL;

		return node;
	}

	static void DestroyNode(Node* node) {
		delete node;
		node = NULL;
	}

public:
	struct Node {
		T Data;

		Node* LeftChild;
		Node* RightSibiling;
	};
};