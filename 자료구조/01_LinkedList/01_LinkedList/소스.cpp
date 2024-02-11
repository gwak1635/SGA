#include <stdio.h>

struct Node
{
	int Data;
	Node* Next;
};


Node* Create(int data) {
	Node* node = new Node();

	node->Data = data;
	node->Next = NULL;

	return node;
}

void Destroy(Node* node){
	delete node;
	node = NULL;
}

void Push(Node** head, Node* node) {
	if ((*head) == NULL) {
		*head = node;
	}
	else {
		Node* tail = (*head);

		while (tail->Next != NULL) {
			tail = tail->Next;
						
		}

		tail->Next = node;

	}
}

void InsertHead(Node** head, Node* node) {
	if (*head == NULL) {
		*head = node;
	}
	else {
		node->Next = *head;
		*head = node;
	}
}

void Remove(Node** head, Node* remove) {
	if (*head == remove) {
		*head = remove->Next;
	}
	else {
		Node* current = *head;
		while (current != NULL && current->Next != remove) {
			current = current->Next;
		}

		if (current != NULL) {
			current->Next = remove->Next;
		}

	}
}

Node* GetNode(Node* head, int location) {
	Node* current = head;

	while (current != NULL && --location >= 0)
		current = current->Next;

	return current;
}

int GetNodeCount(Node* head) {
	int count = 0;
	Node* current = head;

	while (current != NULL) {
		current = current->Next;
		count++;
	}
	return count;
}

int main() {
	Node* list = NULL;
	for (int i = 0; i < 5; i++)
	{
		Node* node = Create(i);
		Push(&list, node);
	}

	int count = GetNodeCount(list);
	for (int i = 0; i < count; i++)
	{
		Node* current = GetNode(list, i);
		printf("List[%d] : %d\n", i, current->Data);
	}
	printf("\n");

	Node* temp = GetNode(list, 3);
	printf("List[%d] : %d\n", 3, temp->Data);
	printf("\n");

	Node* newNode = Create(-1);
	InsertHead(&list, newNode);

	count = GetNodeCount(list);
	for (int i = 0; i < count; i++)
	{
		Node* current = GetNode(list, i);
		printf("List[%d] : %d\n", i, current->Data);
	}
	printf("\n");

	Remove(&list, temp);
	count = GetNodeCount(list);
	for (int i = 0; i < count; i++)
	{
		Node* current = GetNode(list, i);
		printf("List[%d] : %d\n", i, current->Data);
	}
	printf("\n");

	Remove(&list, temp);
	count = GetNodeCount(list);
	for (int i = 0; i < count; i++)
	{
		Node* current = GetNode(list, i);
		printf("List[%d] : %d\n", i, current->Data);
	}
	printf("\n");

	return 0;
}