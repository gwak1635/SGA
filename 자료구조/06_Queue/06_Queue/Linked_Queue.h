#pragma once

template <typename T>
class Circular_Queue
{
public:
	struct Node;

	~Linked_Queue()
	{
		while (IsEmpty() == false)
		{
			delete
		}
	}

	bool IsEmpty()
	{
		return front == NULL;
	}

private:
	struct Node
	{
		T Data;
		Node* Next;
	};

	Node* front = NULL;
	Node* rear = NULL;
}