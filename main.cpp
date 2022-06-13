#include "Stage.h"
#include "AStar.h"

#include <iostream>
#include <sys/resource.h>
#include "BFS.h"
#include <fstream>



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
    std::cout << "3. testy\n";
    int a;
    std::cin >> a; 

    // wybor rozmiaru planszy



    switch (a)
    {
    case 1:
        {
            std::cout << "Podaj rozmiar planszy: ";
            int s;
            std::cin >> s;

            if (s<1) return -1;

            // generowanie planszy
            Stage* stage = new Stage(s);
            // pobranie ilosci uzytych zasobow przez tworzenie planszy
            long stage_memory = get_mem_usage();
            BFS* bfs = new BFS(stage->getBoard(), stage->getSize());    
            std::cout << bfs->getPath();
            long current_mem = get_mem_usage();
            std::cout << "\n\nPotrzebna ilość pamięci RAM dla algorytmu wyszukiwania wszerz: " << current_mem - stage_memory <<"kB\n\n";
        }
        break;
    case 2:
        {
            std::cout << "Podaj rozmiar planszy: ";
            int s;
            std::cin >> s;

            if (s<1) return -1;

            // generowanie planszy
            Stage* stage = new Stage(s);
            // pobranie ilosci uzytych zasobow przez tworzenie planszy
            long stage_memory = get_mem_usage();
            AStar *astar = new AStar(stage->getBoard(), stage->getSize());

            AStar::Vec2 start(0, 0);
            AStar::Vec2 end(s-1, s-1);

            std::vector<AStar::Node*> path = astar->calculatePath(start, end);
            long current_mem = get_mem_usage();
            std::cout << "\n\nPotrzebna ilość pamięci RAM dla algorytmu A*: " << current_mem - stage_memory <<"kB\n\n";
            
        }
        break;

    case 3:
    {
        //generating maps
        int i=1;
        int map_size = 100;
        while (i < 101)
        {
            Stage * stage = new Stage(map_size);
            BFS * bfs = new BFS(stage->getBoard(), stage->getSize());
            if (bfs->getPath() != -1)
            {
                stage->saveCurrentMap();
                i++;
            }
            delete stage;
        }

        // test bfs

        // for (int i = 9; i < 18; i++)
        // {
        //     Stage * s = new Stage(100 * (i+1));
        //     s->loadMap(i);
        //     long mem = get_mem_usage();
        //     AStar *astar = new AStar(s->getBoard(), s->getSize());

        //     AStar::Vec2 start(0, 0);
        //     AStar::Vec2 end(s->getSize()-1, s->getSize()-1);

        //     std::vector<AStar::Node*> path = astar->calculatePath(start, end);
        //     BFS * bfs = new BFS(s->getBoard(), s->getSize());
        //     long used_mem = get_mem_usage();

        //     std::cout << "\nUsed mem: " << used_mem - mem << "kB\n";

        //     // delete s;
        // }
    }
        break;

    case 4:
    {
        std::fstream astar_results;

        int map_size;

        std::cout << "Podaj rozmiar mapy: ";
        std::cin >> map_size;

        std::string file_name = "astar_" + map_size + std::string(".csv"); 


        astar_results.open("astar.csv", std::ios::out);

        astar_results << "A*\n";
        astar_results << "Wielkosc mapy, Zuzyta pamiec\n";


        for (int i = 0; i < 40; i++)
        {
            std::string file_to_remove = "map" + i + std::string(".txt");  
            if (!std::remove(file_to_remove.c_str()))
            {
                std::cout << "Error when deleting a file\n";
                break;
            } 
            else
            {
                std::cout << "File deleted\n";
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
            Stage * s = new Stage(map_size);
            s->loadMap(i);
            long mem = get_mem_usage();
            AStar *astar = new AStar(s->getBoard(), s->getSize());

            AStar::Vec2 start(0, 0);
            AStar::Vec2 end(s->getSize()-1, s->getSize()-1);

            std::vector<AStar::Node*> path = astar->calculatePath(start, end);
            long used_mem = get_mem_usage();

            std::cout << "\nUsed mem: " << used_mem - mem << "kB\n";

            astar_results << i << ", " << used_mem - mem << "\n";

        }

        astar_results.close();


        std::cout<< "Done!";
    }
        break;
    case 5: 
    {
        std::fstream bfs_results;

        int map_size;

        std::cout << "Podaj rozmiar mapy: ";
        std::cin >> map_size;

        std::string file_name = "bfs_" + map_size + std::string(".csv"); 


        bfs_results.open("bfs.csv", std::ios::out);

        bfs_results << "BFS, "<< map_size << "\n";
        bfs_results << "Numer proby, Zuzyta pamiec\n";


        for (int i = 0; i < 40; i++)
        {
            std::string file_to_remove = "map" + i + std::string(".txt");  
            if (!std::remove(file_to_remove.c_str()))
            {
                std::cout << "Error when deleting a file\n";
                break;
            } 
            else
            {
                std::cout << "File deleted\n";
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
            Stage * s = new Stage(map_size);
            s->loadMap(i);
            long mem = get_mem_usage();

            BFS * bfs = new BFS(s->getBoard(), s->getSize());
            long used_mem = get_mem_usage();

            std::cout << "\nUsed mem: " << used_mem - mem << "kB\n";

            bfs_results << i << ", " << used_mem - mem << "\n";

        }

        bfs_results.close();


        std::cout<< "Done!";

    }
    
    
    
    default:
        break;
    }

}

