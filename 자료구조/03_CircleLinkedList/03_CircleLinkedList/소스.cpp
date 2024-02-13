#include <stdio.h>

struct Node
{
	Node* Prev;
	int Data;
	Node* Next;
};

Node* Create(int data)
{
	Node* node = new Node();
	node->Data = data;
}

void Destroy(Node* node)
{
	delete node;
	node = NULL;
}

void Push(Node** head, Node* node)
{
	if (*head == NULL)
	{
		*head = node;
		(*head)->Next = *head;
		(*head)->Prev = *head;
	}
	else
	{
		Node* tail = (*head)->Prev;

		//tail->Next->Prev = node;
		(*head)->Prev = node;
		tail->Next = node;

		node->Prev=tail;
		node->Next=(*head);
	}
}

void Insert(Node* current, Node* node) {
	node->Next = current->Next;
	node->Prev = current;

	node->Next->Prev = node;
	current->Next = node;
}

//void Remove(Node** head, Node* remove) {
//	if ((*head) == remove) {
//		(*head)->Prev->Next = remove->Next;
//		(*head)->Next->Prev = remove->Prev;
//
//		*head = remove->Next;
//	}
//	else {
//		remove->Prev->Next = remove->Next;
//		remove->Next->Prev = remove->Prev;
//	}
//	remove->Prev = remove->Next = NULL;
//	Destroy(remove);
//}

void Remove(Node** head, Node* remove) {

	remove->Prev->Next = remove->Next;
	remove->Next->Prev = remove->Prev;
	if ((*head) == remove) {
		*head = remove->Next;
	}
	remove->Prev = remove->Next = NULL;
	Destroy(remove);
}

Node* GetNode(Node* head, int location) {
	Node* current = head;

	while ((--location)>=0)
	{
		if (current->Next == head)
			break;
		else {
			current = current->Next;
		}
	}

	return current;
}

int GetNodeCount(Node* head) {

	int count = 0;
	Node* current = head;

	do {
		current = current->Next;
		count++;
	} while (current != head);
	

	return count;
}
