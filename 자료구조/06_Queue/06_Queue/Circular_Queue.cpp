#include<stdio.h>
#include "Circular_Queue.h"

void main()
{
	Circular_Queue<int> queue(10);
	for (int i = 0; i < 4; i++)
	{
		queue.Enqueue(i);
		printf("Front : %d, Rear : %d\n", queue.Front(), queue.Rear());
	}
	printf("\n");

	for (int i = 0; i < 3; i++)
	{
		printf("Dequeue : %d, ", queue.Deque());
		printf("Front : %d, Rear : %d\n", queue.Front(), queue.Rear());
	}

	int count = 100;
	while (queue.IsFull() == false)
		queue.Enqueue(count++);

	printf("Capacity : %d, Size : %d\n", queue.Capacity(), queue.Size());
	printf("Front : %d, Rear : %d\n", queue.Front(), queue.Rear());
	printf("IsFull : %d\n", (int)queue.IsFull());

	while (queue.IsEmpty() == false) {
		printf("Dequeue : %d, ", queue.Deque());
		printf("Front : %d, Rear : %d\n", queue.Front(), queue.Rear());
	}
}