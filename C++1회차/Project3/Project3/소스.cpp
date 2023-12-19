#include <iostream>
#include <time.h>

using namespace std;

int main(void) {

	srand(time(NULL));
	rand();

	int box[100];

	int answer[100][100];

	for (int i = 0; i < 100; i++) {
		box[i] = i;
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; i < 100; i++) {
			answer[i][j] = -1;
		}
	}

	for (int i = 0; i < 100; i++) {
		int r = rand() % 100;
		int temp = box[r];
		box[r] = box[i];
		box[i] = temp;
	}

	for (int i = 0; i < 100; i++) {
		int a = i;
		for (int j = 0; j < 100; j++)
		{
			if (box[a] == -1)
				break;

			answer[i][j] = box[a];
			int temp = box[a];
			box[a] = -1;
			a = temp;
		}
		
	}


	for (int i = 0; i < 100; i++) {
		if (answer[i][0] == -1)
			continue;
		else {
			cout << "[";
			for (int j = 0; j < 100; j++)
			{
				if (answer[i][j] == -1)
					break;
				else
					cout << answer[i][j] << " ";
			}
			cout << "]" << endl;
		}
	}
}