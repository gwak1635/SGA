#pragma once

/*
템플릿: 함수 또는 클래스를 만들언 내기 위한 틀
*/

template<typename T> //template <class T>


class SingletonBase {

	//싱글톤은 단일 객체여야 하기 때문에 외부에서 생성, 삭제가 불가능하도록 만들기 위해 프로텍트에 넣음.
protected:
	//static: 정적 변수: 프로그램 수명 내내 지속되는 지역 변수
	static T* Instance;//클래스가 될 거임!


	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetInstance(); // 싱글톤 인스턴스 가져오기
	void ReleaseInstance(); // 싱글톤 인스턴스 해제하기

};

template<typename T>
T* SingletonBase<T>::Instance = NULL;

template<typename T>
inline T* SingletonBase<T>::GetInstance()
{
	if (!Instance) {//처음 호출할때 instance 호출
		Instance = new T;
	}
	return Instance;
}

template<typename T>
inline void SingletonBase<T>::ReleaseInstance()
{
	if (Instance) {
		delete Instance;
		Instance = nullptr;
	}
}
