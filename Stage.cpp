#include "Stage.h"

int Stage::generate(int size)
{
	int result[][];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			result[i][j] = 0;
		}
	}

	int r1, r2;
	for (int k = 0; k < 10; k++) 
	{
		r1 = rand() % 49;
		r2 = rand() % 49;
		if (result[r1][r2] != 1) {
			result[r1][r2] = 1;
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << result[i][j];
		}
	}

	return result;
}