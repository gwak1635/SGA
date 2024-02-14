#include "Array_Stack.h"

void main() {
	Stack<int> stack;
	stack.Push(10);
	
	stack.Push(20);
	stack.Pop();

	stack.Push(12);
	stack.Pop();

	stack.Push(4);

	while (stack.IsEmpty() == false)
	{
		printf("%d\n", stack.Pop());
	}
}