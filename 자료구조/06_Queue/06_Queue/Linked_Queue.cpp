#include<stdio.h>
#include "Linked_Queue.h"

void main()
{
	Linked_Queue<int> queue;
	for (int i = 10; i <= 30; i+=10)
	{
		queue.Enqueue(i);
	}
	printf("Size : %d\n", queue.Count());

	while (queue.IsEmpty() == false)
	{
		printf("Data : %d\n", queue.Dequeue());
	}
}