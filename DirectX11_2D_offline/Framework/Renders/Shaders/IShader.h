#pragma once
//I로 시작하면 인터페이스
//부모로서, 자식에게 상속하기 위해서만 존재함.
//순수 가상 함수만 존재함.

class IShader {
public:
	virtual void Create(const wstring path, const string entryName) = 0;//셰이더 만들어주는 함수, 생성자
	//객체 초기화 // 소멸자
	virtual void Clear() = 0;
	//쉐이더 세팅
	virtual void SetShader() = 0;

protected:
	void CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob);

	wstring path = L"";		//쉐이더 파일 경로
	string entryName = "";	//진입점

private:
	void CheckShaderError(HRESULT hr, ID3DBlob* error);
};