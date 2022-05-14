#include <vector>
#include "Stage.h"


struct Node
{
    int x, y, parentX, parentY;
    float g, h, f;
};

class AStar
{
    public:
        AStar(Stage *stage,int startX, int startY, int destX, int destY);

        std::vector<Node> getRoute();

    private:
        float calculateH();



        void calculateRoute(Node start, Node dest);
        std::vector<Node> route;
};

