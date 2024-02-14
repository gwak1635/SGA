#pragma once
#define MAX_STACK_COUNT 5

#include <stdio.h>
#include <assert.h>
#include <Windows.h>

template<typename T> class Stack
{
public:
	Stack()
	{
		memset(values, 0, sizeof(T) * MAX_STACK_COUNT);
		//ZeroMemory(values, sizeof(T) * MAX_STACK_COUNT);
	}

	void Push(T val)
	{
		//조건이 거짓이면 프로그램 중단하는 함수
		//릴리즈 모드에서는 어설트가 없어짐!!!!
		assert(top + 1 < MAX_STACK_COUNT);

		values[++top] = val;
	}

	T Pop()
	{
		bool b = IsEmpty();
		assert(b == false);

		T val = values[top];
		memset(&values[top], 0, sizeof(T));
		top--;

		return val;
	}

	T Front() {
		return values[top];
	}

	T Back()
	{
		assert(top >= 0);

		return values[0];
	}

	bool IsEmpty() {
		return (top < 0) ? true : false;
	}

private:
	int top = -1;

	T values[MAX_STACK_COUNT];
};