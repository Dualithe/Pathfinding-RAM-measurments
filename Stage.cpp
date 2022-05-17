#include <iostream>
#include <ctime>
#include "Stage.h"

#define OBST 4

Stage::Stage(int size)
{
    this->size = size;
    this->board = generateBoard();
}

Stage::Stage(int** board)
{
	this->board = board;
}

Stage::~Stage()
{
    for(int i = 0; i <size; i++)
    {
        delete[] board[i];
    }
}

int** Stage::getBoard()
{
	return board;
}

int Stage::getSize()
{
	return size;
}

int** Stage::generateBoard()
{
	int** result;

    result = new int*[Stage::size]; 

	for (int i = 0; i < Stage::size; i++)
	{
        result[i] = new int[Stage::size];
		for (int j = 0; j < Stage::size; j++)
		{
			result[i][j] = 0;
		}
	}


    srand(time(NULL));

	int r1, r2;
	for (int k = 0; k < Stage::size*OBST; k++) 
	{
		r1 = rand() % Stage::size;
		r2 = rand() % Stage::size;
		result[r1][r2] = 1;
	}
	result[0][0] = 0;
	result[size-1][size-1] = 0;
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