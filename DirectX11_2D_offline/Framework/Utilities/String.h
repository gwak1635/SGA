#pragma once
class String
{
public:
	static void SplitString	(vector<string>* result, string origin, string tok);
	static void SplitString	(vector<wstring>* result, wstring origin, wstring tok);

	static bool StartWith(string str, string comp);
	static bool StartWith(wstring str, wstring comp);

	static bool Contain(string str, string comp);
	static bool Contain(wstring str, wstring comp);

	static bool Replace(string* str, string comp, string rep);
	static bool Replace(wstring* str, wstring comp, wstring rep);

	static string ToString(D3DXVECTOR3 vec3, int precision = 5);
	static wstring ToWstring(D3DXVECTOR3 vec3, int precision = 5);

	static wstring ToWstring(string str);
	static string ToString(wstring str);
};

