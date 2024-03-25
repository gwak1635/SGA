#pragma once

/*
�̱����� ���α׷��� ������ ������ �ϳ���

�������� ����Ҽ��ִ� �����͸� �����ϰ� ����Ҽ� �ֵ��� ����� ����̴�.

Ŭ������ Ư�� �����͸� �ѹ� �����ϸ� ���̻� �������� �ʰ� ������
������ �����͸� �ǳ��ִ� ������� �۵��Ѵ�.

������ ������ Ư���� ������ �޼��ϱ� ���� ����ϴ� ������ �ڵ� ���ʸ�
���Ѵ�.

���� ��� - ��𼭵� ����ϰ����� ������ ����� ���

���ó - �������⼭ �� ���̴µ� 1���� �־���ϴ� Ŭ�������� �̱�������
�����. 
*/

template <typename T>
class SingletonBase
{
public:
	static void Create()
	{
		if (instance == nullptr)
			instance = new T();
	}

	static void Delete()
	{
		delete instance;
		instance = nullptr;
	}

	static T* Get()
	{
		return instance;
	}

protected:
	static T* instance;
};

template<typename T> 
T* SingletonBase<T>::instance = nullptr;