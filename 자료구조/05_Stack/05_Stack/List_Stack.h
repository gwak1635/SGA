#pragma once

#include<Windows.h>
#include<string>
using namespace std;


template<typename T>
class Stack {
public:

	struct Node {
		T Data;
		Node* Next;
	};

	Node* Top() { return top; }
	bool IsEmpty() { return head == NULL; }

	void Push(Node* node) {//멤버 변수 사용할 것이므로 static 안 붙임
		if (head != NULL) {
			Node* tail = head;

			while (tail->Next != NULL)
				tail = tail->Next;

			tail->Next = node;
		}
		else {
			head = node;
		}

		top = node;//top==Tail
	}

	Node* Pop() {
		Node* temp = top;

		if (head == top) {
			head = NULL;
			top = NULL;
		}
		else {
			Node* tail = head;
			while (tail != NULL && tail->Next != top)//top의 바로 전까지 while을 돌려줌
				tail = tail->Next;

			top = tail;
			tail->Next = NULL;
		}
		

		return temp;
	}

	int Size() {
		int count = 0;
		Node* current = head;

		while (current != NULL) {
			current = current->Next;
			count++;
		}
		return count;

	}

	static Node* Create(T data) {
		Node* node = new Node();
		node->Data = data;
		node->Next = NULL;

		return node;
	}

	static void Destroy(Node* node) {
		delete node;
		node = NULL;
	}

	
private:

	Node* top = NULL;
	Node* head = NULL;
};