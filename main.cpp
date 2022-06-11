#include "BFS.h"
#include "Stage.h"
#include <iostream>
#include <sys/resource.h>
#include "AStar.h"

long get_mem_usage()
{
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    return r_usage.ru_maxrss;
}

int main()
{
    // wybor algorytmu
    std::cout << "Wybierz algorytm: \n";
    std::cout << "1. BFS\n";
    std::cout << "2. A*\n";
    std::cout << "...\n";
    int a;
    std::cin >> a; 

    // wybor rozmiaru planszy
    std::cout << "Podaj rozmiar planszy: ";
    int s;
    std::cin >> s;

    if (s<1) return -1;

    // generowanie planszy
    Stage* stage = new Stage(s);

    // pobranie ilosci uzytych zasobow przez tworzenie planszy
    long stage_memory = get_mem_usage();


    switch (a)
    {
    case 1:
        {
            BFS* bfs = new BFS(stage->getBoard(), stage->getSize());    
            std::cout << bfs->getPath();
            long current_mem = get_mem_usage();
            std::cout << "\n\nPotrzebna ilość pamięci RAM dla algorytmu wyszukiwania wszerz: " << current_mem - stage_memory <<"kB\n\n";
        }
        break;
    case 2:
    {

	    AStar astar(stage->getBoard(), stage->getSize());

	    AStar::Vec2 start(0, 0);
        AStar::Vec2 end(s-1, s-1);


        std::vector<AStar::Node*> path = astar.calculatePath(start, end);
        long mem = get_mem_usage();

            for (int i = 0; i < path.size(); i++)
            {
                int x = path[i]->pos.x;
                int y = path[i]->pos.y;
                std::cout << x << ',' << y << '\n';
            }
        std::cout << "\n\nPotrzebna ilość pamięci RAM dla algorytmu A*: " << mem - stage_memory <<"kB\n\n";
        
    }
    default:
        break;
    }




    return 0;
}
