#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include "Stage.h"
#include "AStar.h"



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
	for (int k = 0; k < Stage::size*2 ; k++) 
	{
		r1 = rand() % Stage::size;
		r2 = rand() % Stage::size;
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


int** Stage::getBoard() 
{
	return this->board;
}

int Stage::getSize()
{
	return this->size;
}

void Stage::displayPath() {
	for (int i = 0; i < Stage::size; i++)
	{
		for (int j = 0; j < Stage::size; j++)
		{
				std::cout << Stage::board[i][j] << " ";
		}
		std::cout << std::endl;
	}

}


	void Stage::saveCurrentMap() {
		std::ofstream file;
		for (int i = 0; i < 1000; i++) {
			if (!fileExists("map" + std::to_string(i) + ".txt")) {
				file.open("map" + std::to_string(i) + ".txt");
				i = 1000;
			}
		}

		file << size;
		file << std::endl;
		for (int i = 0; i < Stage::size; i++)
		{
			for (int j = 0; j < Stage::size; j++)
			{
				file << Stage::board[i][j] << " ";
			}
			file << std::endl;
		}
		file.close();
		std::cout << "Saved!";

	}

	bool Stage::fileExists(std::string filename) {
		std::ifstream infile(filename);
		return infile.good();
	}

	void Stage::loadMap(int mapNum) {

		std::ifstream file;
		file.open("map" + std::to_string(mapNum) + ".txt");
		file >> size;

		std::string s;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				std::getline(file, s, ' ');
				Stage::board[i][j] = std::stoi(s);
			}
		}

		file.close();
		std::cout << "Loaded!";
	}


	