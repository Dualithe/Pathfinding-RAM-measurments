#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include "AStar.h"


AStar::AStar(int** board, int size)
{
	this->size = size;
	this->board = board;
}


bool AStar::isPosValid(AStar::Vec2 pos)
{
	return pos.x >= 0 && pos.y >= 0 && pos.x < size&& pos.y < size&& board[pos.x][pos.y] != 1;
}

std::vector<AStar::Vec2> AStar::getAdjacentPos(AStar::Vec2 pos)
{

	std::vector<AStar::Vec2> result;

	AStar::Vec2 upper = AStar::Vec2(pos.x, pos.y + 1);
	if (isPosValid(upper)) result.push_back(upper);

	AStar::Vec2 lower = AStar::Vec2(pos.x, pos.y - 1);
	if (isPosValid(lower)) result.push_back(lower);

	AStar::Vec2 left = AStar::Vec2(pos.x - 1, pos.y);
	if (isPosValid(left)) result.push_back(left);

	AStar::Vec2 right = AStar::Vec2(pos.x + 1, pos.y);
	if (isPosValid(right)) result.push_back(right);

	AStar::Vec2 topright = AStar::Vec2(pos.x + 1, pos.y + 1);
	if (isPosValid(topright)) result.push_back(topright);

	AStar::Vec2 bottomright = AStar::Vec2(pos.x + 1, pos.y - 1);
	if (isPosValid(bottomright)) result.push_back(bottomright);

	AStar::Vec2 topleft = AStar::Vec2(pos.x - 1, pos.y + 1);
	if (isPosValid(topleft)) result.push_back(topleft);

	AStar::Vec2 bottomleft = AStar::Vec2(pos.x - 1, pos.y - 1);
	if (isPosValid(bottomleft)) result.push_back(bottomleft);

	return result;
}

void AStar::tryAddToOpen(AStar::Vec2 pos, int g, int h, AStar::Node* parent)
{
	for (AStar::Node* node : openList)
	{
		if (node->pos.x == pos.x && node->pos.y == pos.y)
		{
			return;
		}
	}
	for (AStar::Node* node : closedList)
	{
		if (node->pos.x == pos.x && node->pos.y == pos.y)
		{
			return;
		}
	}

	AStar::Node* newNode = new AStar::Node;
	newNode->g = g;
	newNode->h = h;
	newNode->f = g + h;
	newNode->pos = pos;
	newNode->parent = parent;
	openList.push_back(newNode);
}

std::vector<AStar::AStar::Node*> AStar::calculatePath(AStar::Vec2 startPos, AStar::Vec2 endPos)
{
	calculate(startPos, endPos);
	return getPath();
}

void AStar::calculate(AStar::Vec2 startPos, AStar::Vec2 endPos)
{
	endNode = NULL;

	openList.clear();
	closedList.clear();

	int h = std::abs(startPos.x - endPos.x) + std::abs(startPos.y - endPos.y);
	tryAddToOpen(startPos, 0, h, NULL);

	while (openList.size() > 0)
	{
		AStar::Node* currentNode = popBestNode();

		if (currentNode->pos.x == endPos.x && currentNode->pos.y == endPos.y)
		{
			endNode = currentNode;
			break;
		}

		std::vector<AStar::Vec2> poses = getAdjacentPos(currentNode->pos);

		for (AStar::Vec2 pos : poses)  //foreach
		{
			int g = currentNode->g + 10;
			int h = std::abs(pos.x - endPos.x) + std::abs(pos.y - endPos.y);
			tryAddToOpen(pos, g, h, currentNode);
		}
	}
}

std::vector<AStar::Node*> AStar::getPath()
{
	std::vector<AStar::Node*> path;

	if (endNode != NULL)
	{
		AStar::Node* node = endNode;
		do {
			path.push_back(node);
			node = node->parent;

		} while (node != NULL);
		std::reverse(path.begin(), path.end());
	}

	return path;
}

AStar::Node* AStar::popBestNode()
{
	int minF = 1000000;


	for (AStar::Node* node : openList)
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
		AStar::Node* node = openList[i];
		if (node->f == minF && node->h < minH)
		{
			minH = node->h;
			bestNodeIdx = i;
		}
	}

	AStar::Node* bestNode = openList[bestNodeIdx];
	openList.erase(openList.begin() + bestNodeIdx);
	closedList.push_back(bestNode);
	return bestNode;
}
