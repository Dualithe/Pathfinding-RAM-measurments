#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>



class AStar {

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

private:
	int size;
	int** board;

	std::vector<Node*> closedList;
	std::vector<Node*> openList;
	Node* endNode = NULL;

public:


	AStar(int** board, int size)
	{
		this->size = size;
		this->board = board;
	}


	bool isPosValid(Vec2 pos)
	{
		return pos.x >= 0 && pos.y >= 0 && pos.x < size&& pos.y < size&& board[pos.x][pos.y] != 1;
	}

	std::vector<Vec2> getAdjacentPos(Vec2 pos)
	{

		std::vector<Vec2> result;

		Vec2 upper = Vec2(pos.x, pos.y + 1);
		if (isPosValid(upper)) result.push_back(upper);

		Vec2 lower = Vec2(pos.x, pos.y - 1);
		if (isPosValid(lower)) result.push_back(lower);

		Vec2 left = Vec2(pos.x - 1, pos.y);
		if (isPosValid(left)) result.push_back(left);

		Vec2 right = Vec2(pos.x + 1, pos.y);
		if (isPosValid(right)) result.push_back(right);

		Vec2 topright = Vec2(pos.x + 1, pos.y + 1);
		if (isPosValid(topright)) result.push_back(topright);

		Vec2 bottomright = Vec2(pos.x + 1, pos.y - 1);
		if (isPosValid(bottomright)) result.push_back(bottomright);

		Vec2 topleft = Vec2(pos.x - 1, pos.y + 1);
		if (isPosValid(topleft)) result.push_back(topleft);

		Vec2 bottomleft = Vec2(pos.x - 1, pos.y - 1);
		if (isPosValid(bottomleft)) result.push_back(bottomleft);

		return result;
	}

	void tryAddToOpen(Vec2 pos, int g, int h, Node* parent)
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

	std::vector<Node*> calculatePath(Vec2 startPos, Vec2 endPos)
	{
		calculate(startPos, endPos);
		return getPath();
	}

	void calculate(Vec2 startPos, Vec2 endPos)
	{
		endNode = NULL;
		while (!openQueue.empty()) {
			openQueue.pop();
		}
		while (!closedQueue.empty()) {
			closedQueue.pop();
		}

		openList.clear();
		closedList.clear();

		int h = std::abs(startPos.x - endPos.x) + std::abs(startPos.y - endPos.y);
		tryAddToOpen(startPos, 0, h, NULL);

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
				tryAddToOpen(pos, g, h, currentNode);
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
				path.push_back(node);
				node = node->parent;

			} while (node != NULL);
			std::reverse(path.begin(), path.end());
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

		int bestNodeIdx;

		for (int i = 0; i < openList.size(); i++)
		{
			Node* node = openList[i];
			if (node->f == minF && node->h < minH)
			{
				minH = node->h;
				bestNodeIdx = i;
			}
		}

		Node* bestNode = openList[bestNodeIdx];
		openList.erase(openList.begin() + bestNodeIdx);
		closedList.push_back(bestNode);
		return bestNode;
	}
};