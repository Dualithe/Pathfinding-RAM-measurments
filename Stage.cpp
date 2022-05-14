<<<<<<< HEAD
#include "Stage.h"

int Stage::generate(int size)
{
	int result[][];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
=======
#include <iostream>
#include <ctime>
#include "Stage.h"


Stage::Stage(int size)
{
    this->size = size;
    this->board = generateBoard();
}
Stage::~Stage()
{
    for(int i = 0; i <size; i++)
    {
        delete[] board[i];
    }
}



int** Stage::generateBoard()
{
	int** result;

    result = new int*[Stage::size]; 

	for (int i = 0; i < Stage::size; i++)
	{
        result[i] = new int[Stage::size];
		for (int j = 0; j < Stage::size; j++)
>>>>>>> 29e8605 (Generate board)
		{
			result[i][j] = 0;
		}
	}

<<<<<<< HEAD
	int r1, r2;
	for (int k = 0; k < 10; k++) 
	{
		r1 = rand() % 49;
		r2 = rand() % 49;
		if (result[r1][r2] != 1) {
=======
    srand(time(NULL));

	int r1, r2;
	for (int k = 0; k < Stage::size ; k++) 
	{
		r1 = rand() % Stage::size + 1;
		r2 = rand() % Stage::size + 1;
		if (result[r1][r2] != 1) 
        {
>>>>>>> 29e8605 (Generate board)
			result[r1][r2] = 1;
		}
	}

<<<<<<< HEAD
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << result[i][j];
		}
	}

	return result;
}
=======
	return result;
} 


void Stage::displayBoard()
{
	for (int i = 0; i < Stage::size; i++)
	{
		for (int j = 0; j < Stage::size; j++)
		{
			std::cout << Stage::board[i][j] << " ";
		}
        std::cout << std::endl;
	}
}

>>>>>>> 29e8605 (Generate board)
