#pragma once

/*
싱글턴은 프로그래밍 디자인 패턴중 하나로

전역에서 사용할수있는 데이터를 안전하게 사용할수 있도록 만드는 기능이다.

클래스에 특정 데이터를 한번 생성하면 더이상 생성하지 않고 이전에
생성한 데이터를 건내주는 방식으로 작동한다.

디자인 패턴은 특정한 목적을 달성하기 위해 사용하는 일종의 코드 관례를
말한다.

한줄 요약 - 어디서든 사용하가능한 데이터 만드는 기능

사용처 - 여기저기서 다 쓰이는데 1개만 있어야하는 클래스들은 싱글턴으로
만든다. 
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