#pragma once


class Random
{
public:
	static int GetRandomInt(int minI, int maxI);
	static float GetRandomFloat(float minF, float maxF);
	//퍼블릭 함수만 있으면 컴포넌트라고도 부름.(객체라기엔 좀 애매-해서!)
};