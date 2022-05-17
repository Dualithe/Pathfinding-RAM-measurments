#include "Stage.h"
#include "AStar.h"
#include <stdio.h>
#include <iostream>


int main()
{

	Stage* stage = new Stage(10);

	stage->displayBoard();

	AStar astar(stage->getBoard(), stage->getSize());

	AStar::Vec2 start(0, 0);
	AStar::Vec2 end(9, 9);


	std::vector<AStar::Node*> path = astar.calculatePath(start, end);
	for (int i = 0; i < path.size(); i++)
	{
		int x = path[i]->pos.x;
		int y = path[i]->pos.y;
		std::cout << x << ',' << y << '\n';
	}
}