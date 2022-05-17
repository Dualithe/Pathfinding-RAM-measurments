#include <iostream>
#include <ctime>
#include "AStar.h"
#include <vector>



class AStar() {
	int size;
	int** board;

	std::vector<Node*> closedList;
	std::vector<Node*> openList;
	Node* endNode = NULL;

public:

	struct Vec2
	{
		int x;
		int y;
		Vec2(int x, int y)

		{
			this->x = x;
			this->y = y;
		}
		Vec2()
		{
			x = 0;
			y = 0;
		}
	};

	struct Node
	{
		Vec2 pos;
		int g = 0;
		int h = 0;
		int f = 0; //g+h
		Node* parent = NULL;
	};


	AStar(int** board, int size)
	{
		this->size = size;
		this->board = board;
	}


	bool isPosValid(Vec2 pos)
	{
		return pos.x >= 0 && pos.y >= 0 && pos.x < size&& pos.y < size;
	}

	std::vector<Vec2> getAdjacentPos(Vec2 vec)
	{

		std::vector<vec> result;

		vec upper = Vec2(pos.x, pos.y + 1);
		if (isPosValid(upper)) result.push_back(upper);

		vec lower = Vec2(pos.x, pos.y - 1);
		if (isPosValid(lower)) result.push_back(lower);

		vec left = Vec2(pos.x - 1, pos.y);
		if (isPosValid(left)) result.push_back(left);

		vec right = Vec2(pos.x + 1, pos.y);
		if (isPosValid(right)) result.push_back(right);


		return result;
	}

	void TryAddToOpen(Vec2 pos, int g, int h, Node * parent)
	{
		for (Node* node : openList)
		{
			if (node->pos.x == pos.x && node->pos.y == pos.y)
			{
				return;
			}
		}
		for (Node* node : closedList)
		{
			if (node->pos.x == pos.x && node->pos.y == pos.y)
			{
				return;
			}
		}

		Node* newNode = new Node;
		newNode->g = g;
		newNode->h = h;
		newNode->f = g + h;
		newNode->pos = pos;
		newNode->parent = parent;
		openList.push_back(newNode);
	}

	std::vector<Node*> calculatePath(Vec2 startPos,Vec2 endPos) 
	{
		calculate();
		getPath();
	}

	void calculate(Vec2 startPos, Vec2 endPos)
	{

		int h = std::abs(startPos.x - endPos.x) + std::abs(startPos.y - endPos.y);
		tryAddToOpen(startPos, 0, h);

		while (openList.size() > 0)
		{
			Node* currentNode = popBestNode();

			if (currentNode->pos.x == endPos.x && currentNode->pos.y == endPos.y)
			{
				endNode = currentNode;
				break;
			}

			std::vector<Vec2> poses = getAdjacentPos(currentNode->pos);

			for (Vec2 pos : poses)  //foreach
			{
				int g = currentNode->g + 10;
				int h = std::abs(pos.x - endPos.x) + std::abs(pos.y - endPos.y);
				TryAddToOpen(pos, g, h, currentNode);
			}
		}
	}

	std::vector<Node*> getPath()
	{
		std::vector<Node*> path;

		if (endNode != NULL)
		{
			Node* node = endNode;
			do {
				path.push_front(node);
				node = node->parent;

			} while (node != NULL);
		}

		return path;
	}

	Node* popBestNode()
	{
		int minF = 1000000;


		for (Node* node : openList)
		{
			if (node->f < minF)
			{
				minF = node->f;
			}
		}


		int minH = 1000000;

		Node bestNodeIdx;

		for (int i = 0; i < openList.size(); i++)
		{
			Node* node = openList[i];
			if (node->f == minF && node->h < minH)
			{
				minH = node->h;
				bestNodeIdx = i;
			}
		}

		Node* bestNode = openList[i];
		openList.remove(openList.begin() + i);
		closedList.push_back(bestNode);
		return bestNode;
	}

}


























