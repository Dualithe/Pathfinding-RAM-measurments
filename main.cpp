#include "Stage.h"
#include "AStar.h"
#include <cstdio>
#include <iostream>
#include <sys/resource.h>
#include "BFS.h"
#include <fstream>
#include <unistd.h>


long get_phys_mem_usage()
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
    std::cout << "3. testy\n";
    int a;
    std::cin >> a; 

    // wybor rozmiaru planszy



    switch (a)
    {
    case 2:
    {
        std::fstream astar_results;

        int map_size;

        std::cout << "Podaj rozmiar mapy: ";
        std::cin >> map_size;

        std::string file_name = "astar_" + map_size + std::string(".csv"); 


        astar_results.open("astar_" + std::to_string(map_size) + ".csv", std::ios::out);

        astar_results << "A*\n";
        astar_results << "Numer proby, Zuzyta pamiec\n";


        for (int i = 0; i < 40; i++)
        {
            std::string file_to_remove_string = "map" + std::to_string(i) + ".txt"; 

            const char* file_to_remove = file_to_remove_string.c_str();

            int remove_result = remove(file_to_remove);

            if (!remove_result)
            {
                std::cout << "File deleted\n" << remove_result << "\n";
            } 
            else
            {
                std::cout << "Error when deleting a file\n";
                std::cout << "\n";
            }
        }
        

        int i = 0;
        while (i < 40)
        {
            Stage * stage = new Stage(map_size);
            BFS * bfs = new BFS(stage->getBoard(), stage->getSize());
            if (bfs->getPath() != -1)
            {
                stage->saveCurrentMap();
                std::cout << "Map generated\n";
                i++;
            }
            delete stage;
        }




        for (int i = 0; i < 40; i++)
        {
        	srand(time(NULL));
            Stage * s = new Stage(map_size);
            s->loadMap(i);
            long mem = get_phys_mem_usage();
            AStar *astar = new AStar(s->getBoard(), s->getSize());

            AStar::Vec2 start(0, 0);
            AStar::Vec2 end(s->getSize()-1, s->getSize()-1);

            std::vector<AStar::Node*> path = astar->calculatePath(start, end);
            long used_mem = get_phys_mem_usage();

            std::cout << "\nUsed mem: " << used_mem - mem << "kB\n";

            astar_results << i << ", " << used_mem - mem << "\n";

        }

        astar_results.close();


        std::cout<< "Done!";
    }
        break;
    case 1: 
    {
        std::fstream bfs_results;

        int map_size;

        std::cout << "Podaj rozmiar mapy: ";
        std::cin >> map_size;

        bfs_results.open("bfs_" + std::to_string(map_size) + ".csv", std::ios::out);

        bfs_results << "BFS, "<< map_size << "\n";
        bfs_results << "Numer proby, Zuzyta pamiec\n";


        for (int i = 0; i < 40; i++)
        {
            std::string file_to_remove_string = "map" + std::to_string(i) + ".txt"; 

            const char* file_to_remove = file_to_remove_string.c_str();

            int remove_result = remove(file_to_remove);

            if (!remove_result)
            {
                std::cout << "File deleted\n" << remove_result << "\n";
            } 
            else
            {
                std::cout << "Error when deleting a file\n";
                std::cout << "\n";
            }
        }
        

        int i = 0;
        while (i < 40)
        {
            Stage * stage = new Stage(map_size);
            BFS * bfs = new BFS(stage->getBoard(), stage->getSize());
            if (bfs->getPath() != -1)
            {
                stage->saveCurrentMap();
                std::cout << "Map generated\n";
                i++;
            }
        }

        for (int i = 0; i < 40; i++)
        {
        	srand(time(NULL));
            Stage * s = new Stage(map_size);
            s->loadMap(i);
            long mem = get_phys_mem_usage();

            BFS * bfs = new BFS(s->getBoard(), s->getSize());
            long used_mem = get_phys_mem_usage();

            std::cout << "\nUsed mem: " << used_mem - mem << "kB\n";

            bfs_results << i << ", " << used_mem - mem << "\n";

        }

        bfs_results.close();


        std::cout<< "Done!\n";

    }
    
    
    
    default:
        break;
    }

}

