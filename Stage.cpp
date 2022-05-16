#include <iostream>
#include <ctime>
#include "Stage.h"



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
	for (int k = 0; k < Stage::size*10 ; k++) 
	{
		r1 = rand() % Stage::size + 1;
		r2 = rand() % Stage::size + 1;
		if (result[r1][r2] != 1) 
        {
			result[r1][r2] = 1;
		}
	}

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

void Stage::setBoard(int** value)
{
	this->board = value;
}