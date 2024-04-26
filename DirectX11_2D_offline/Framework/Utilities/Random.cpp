#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int minI, int maxI)
{
	random_device randDevices;

	uniform_int_distribution<int> intRand(minI, maxI);

	int temp = intRand(randDevices);

	return temp;
}

float Random::GetRandomFloat(float minF, float maxF)
{
	random_device randDevices;

	uniform_real_distribution<float> floatRand(minF, maxF);

	float temp = floatRand(randDevices);

	return temp;
}
