#include <iostream>
#include <time.h>

using namespace std;

int main() {
	srand(time(NULL));
	rand();

	int maya = 0;
	int kikyo = 0;

	for (int i = 0; i < 10001; i++)
	{
		if (rand() % 2 == 0) {
			maya++;
		}
		else {
			kikyo++;
		}
	}
	

	cout << "���� : " <<maya<< endl;
	cout << "Ű�� : " << kikyo << endl;
	return 0;
}