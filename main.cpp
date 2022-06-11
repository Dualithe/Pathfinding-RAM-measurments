#include "Stage.h"
#include "AStar.h"
#include <stdio.h>
#include <iostream>


int main()
{

	Stage* stage = new Stage(10);

	stage->displayBoard();
	std::cout << std::endl;

	stage->saveCurrentMap();
	std::cout << std::endl;

	AStar astar(stage->getBoard(), stage->getSize());

	AStar::Vec2 start(0, 0);
	AStar::Vec2 end(9, 9);

	std::cout << std::endl;
	std::vector<AStar::Node*> path = astar.calculatePath(start, end);
	for (int i = 0; i < path.size(); i++)
	{
		int x = path[i]->pos.x;
		int y = path[i]->pos.y;
		std::cout << x << ',' << y << '\n';
	}
	std::cout << std::endl;
	Stage* stage2 = new Stage(30);
	stage2->displayBoard();
	std::cout << std::endl;
	stage2->loadMap(1);
	std::cout << std::endl;
	std::cout << std::endl;
	stage2->displayBoard();
}