#include "stdafx.h"

int main()
{
    srand(time(NULL));
    rand();


    vector<int> vecInt;
    for (int i = 1; i <= 10; i++)
    {
        vecInt.push_back(i);
    }

    for (int i = 0; i < 100; i++)
    {
        int nSrc = rand() % 10;
        int nDest = rand() % 10;

        int nTemp = vecInt[nSrc];
        vecInt[nSrc] = vecInt[nDest];
        vecInt[nDest] = nTemp;
    }
    
    for (int i = 0; i < vecInt.size(); i++)
    {
        cout << vecInt[i] << endl;
    }

    for (int i = 0; i < vecInt.size(); i++)
    {
        if (vecInt[i] == 5)
            vecInt.erase(vecInt.begin()+i);
    }

    for (int i = 0; i < vecInt.size(); i++)
    {
        cout << vecInt[i] << endl;
    }
}