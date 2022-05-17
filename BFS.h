#include <vector>
struct Point
{
    int x;
    int y;
};
struct Node
{
    Point pt;  
    int dist;  
};

class BFS
{

    public:
        BFS(int** board, int size);
        ~BFS();
        int getPath();
        int findPath(int** board, int size);

    private:
        int minDistance();
        bool isValid(int row, int col, int size);

        int path;

};