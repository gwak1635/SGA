#pragma once

template <typename T>
class Linked_Queue
{
private:
	struct Node;

public:
	~Linked_Queue()
	{
		while (IsEmpty() == false)
		{
			Dequeue();
		}
	}

	bool IsEmpty()
	{
		return front == NULL;
	}

	int Count() {
		return count;
	}

	void Enqueue(T data)
	{
		Node* node = new Node();
		node->Data = data;

		if (front == NULL) {
			front = node;
			rear = node;
		}
		else {
			rear->Next = node;
			rear = node;
		}
		count++;
	}

	T Dequeue() {
		Node* node = front;

		if(front->Next == NULL)//하나밖에 안 남았을 때
			front = rear = NULL;
		else
			front = front->Next;

			count--;

			T val = node->Data;

			delete node;
			node = NULL;

			return val;
	}

private:
	struct Node
	{
		T Data;
		Node* Next;
	};

	Node* front = NULL;
	Node* rear = NULL;

	int count = 0;
};