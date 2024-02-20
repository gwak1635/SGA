#include <stdio.h>
#include "Timer.h"
#include <algorithm>
#include <random>
#include <Windows.h>
void ArrSwap(int* dataSet, int length) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(dataSet, dataSet + length, gen);
	
}

bool IsSorted(int* datas, int length) {
	for (int i = 0; i < length-1; i++)
	{
		if (datas[i] > datas[i + 1])
			return false;
	}
	return true;
}

void BubbleSort(int* dataSet, int Length) {
	for (int i = 0; i < Length - 1; i++) {
		bool isComplete = true;
		for (int j = 0; j < Length - (i + 1); j++) {//한 번의 정렬 당 하나의 최댓값이 오른쪽으로 고정됨
			if (dataSet[j] > dataSet[j + 1])
			{
				int temp = dataSet[j + 1];
				dataSet[j + 1] = dataSet[j];
				dataSet[j] = temp;
				isComplete = false;
			}
		}//for(j)
		if (isComplete)
			return;
	}//for(i)
}

void InsertSort(int* data, int Length) {
	for (int i = 1; i < Length; i++) {
		if (data[i] > data[i - 1]) {
			int value = data[i];
			for (int j = 0; j < i; j++)
			{
				if (data[j] > value)
				{
					memmove(&data[j + 1], &data[j], sizeof(data[0]) * (i - j));
					data[j] = value;
					break;
				}
			}//for(j)	
		}
	}//for(I)
}

void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(int* datas, int left, int right) {
	int first = left;
	int pivot = datas[first];

	left++;
	while (left <= right)
	{	
		while (datas[left] <= pivot && left < right)
			left++;
		while (datas[right] > pivot && left <= right)
			right--;

		if (left < right)
			Swap(&datas[left], &datas[right]);
		else
			break;
	}
	
	Swap(&datas[first], &datas[right]);

	return right;
}

void QSort(int* datas, int left, int right)
{

	if (left < right)
	{
		int index = Partition(datas, left, right);

		QSort(datas, left, index - 1);
		QSort(datas, index + 1, right);
	}
}

int Compare(const void* val1, const void* val2) {
	int* left = (int*)val1;
	int* right = (int*)val2;
	if (*left > *right)
		return 1;
	else if (*left < *right)
		return -1;
	else
		return 0;
}

bool Compare2(const int& val1, const int& val2) {
	return val1 < val2;
}

void MoveSwapping(int* swapping, int* dataset, int length) {
	for (int i = 0; i < length; i++)
	{
		swapping[i] = dataset[i];
	}
}

void main()
{
	Timer timer;
	int dataSet[65536];
	int SwappingdataSet[65536];
	int length = sizeof(dataSet) / sizeof(int);

	for (int i = 0; i < length; i++)
	{
		dataSet[i] = i + 1;
	}
	ArrSwap(dataSet, length);

	MoveSwapping(SwappingdataSet, dataSet, length);
	timer.Start();
	BubbleSort(SwappingdataSet, length);
	double t = timer.End();
	printf("버블정렬 수행시간(ms) : %lf\n", t);

	MoveSwapping(SwappingdataSet, dataSet, length);
	timer.Start();
	InsertSort(SwappingdataSet, length);
	t = timer.End();
	printf("삽입정렬 수행시간(ms) : %lf\n", t);

	MoveSwapping(SwappingdataSet, dataSet, length);
	timer.Start();
	QSort(SwappingdataSet, 0, length-1);
	t = timer.End();
	printf("직접 만든 퀵 정렬 수행시간(ms) : %lf\n", t);

	MoveSwapping(SwappingdataSet, dataSet, length);
	timer.Start();
	qsort(SwappingdataSet, length,sizeof(int),Compare);
	t = timer.End();
	printf("C스타일 퀵 정렬 수행시간(ms) : %lf\n", t);

	MoveSwapping(SwappingdataSet, dataSet, length);
	timer.Start();
	std::sort(SwappingdataSet, SwappingdataSet + length - 1);
	t = timer.End();
	printf("C++스타일 퀵 정렬 수행시간(ms) : %lf\n", t);

	timer.Start();
	QSort(SwappingdataSet, 0, length - 1);
	t = timer.End();
	printf("최악의 퀵 정렬 수행시간(ms) : %lf\n", t);

	timer.Start();
	qsort(SwappingdataSet, length, sizeof(int), Compare);
	t = timer.End();
	printf("최악의 C스타일 퀵 정렬 수행시간(ms) : %lf\n", t);

	timer.Start();
	std::sort(SwappingdataSet, SwappingdataSet + length - 1);
	t = timer.End();
	printf("최악의 C++스타일 퀵 정렬 수행시간(ms) : %lf\n", t);


	//정렬 전
	//for (int i = 0; i < length; i++)
	//{
	//	printf("%d ", BubbledataSet[i]);
	//}
	//printf("\n");

	//정렬 후
	//for (int i = 0; i < length; i++)
	//{
	//	printf("%d ", BubbledataSet[i]);
	//}
	//printf("\n");
}