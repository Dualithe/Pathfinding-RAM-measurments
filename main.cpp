#include "BFS.h"
#include "Stage.h"
#include <iostream>
#include <sys/resource.h>

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

    default:
        break;
    }




    return 0;
}
