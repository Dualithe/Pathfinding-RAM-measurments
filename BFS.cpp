#include "BFS.h"
#include <vector>
#include <queue>
#include <iostream>

BFS::BFS(int** board, int size)
{
    path = findPath(board, size);
}


int BFS::getPath()
{
    return path;
}

bool BFS::isValid(int row, int col, int size)
{
    return (row >= 0) && (row < size) && (col >= 0) && (col < size);
}

int BFS::findPath(int** board, int size)
{
    Point src = {0, 0};
    Point dest = {size-1, size-1};

    bool **visited = new bool*[size];
    for(int i = 0; i < size; i++) 
    {
        visited[i] = new bool[size];
        for (int j = 0; j < size; j++)
        {
            visited[i][j] = false;
        }
    }


    visited[src.x][src.y] = true;

    int rowNum[] = {-1, 0, 0, 1, 1,  1, -1, -1};
    int colNum[] = {0, -1, 1, 0, 1, -1,  1, -1};


    
    std::queue<Node> q;
    Node s = {src, 0, NULL};

    q.push(s);

    while (!q.empty())
    {
        Node curr = q.front();
        Point pt = curr.pt;

        if ((pt.x == dest.x) && (pt.y == dest.y))
        {
            for(int i = 0; i < size; i++) 
            {
                delete[] visited[i] ;
            }
            delete[] visited;
            return curr.dist;
        }

        q.pop();

        for (int i = 0; i < 8; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];


            if (isValid(row, col, size) && board[row][col]==0 && !visited[row][col])
            {

                visited[row][col] = true;
                Node Adjcell = {    {row, col},
                                    curr.dist + 1, &curr};
                q.push(Adjcell);
            }
        }
    }
    for(int i = 0; i < size; i++) 
    {
        delete[] visited[i] ;
    }
    delete[] visited;
    return -1;
}