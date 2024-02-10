#pragma once

/*
���ø�: �Լ� �Ǵ� Ŭ������ ����� ���� ���� Ʋ
*/

template<typename T> //template <class T>


class SingletonBase {

	//�̱����� ���� ��ü���� �ϱ� ������ �ܺο��� ����, ������ �Ұ����ϵ��� ����� ���� ������Ʈ�� ����.
protected:
	//static: ���� ����: ���α׷� ���� ���� ���ӵǴ� ���� ����
	static T* Instance;//Ŭ������ �� ����!


	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetInstance(); // �̱��� �ν��Ͻ� ��������
	void ReleaseInstance(); // �̱��� �ν��Ͻ� �����ϱ�

};

template<typename T>
T* SingletonBase<T>::Instance = NULL;

template<typename T>
inline T* SingletonBase<T>::GetInstance()
{
	if (!Instance) {//ó�� ȣ���Ҷ� instance ȣ��
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
