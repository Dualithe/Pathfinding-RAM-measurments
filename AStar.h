#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>



class AStar {

public:

    struct Vec2
    {
        int x;
        int y;
        Vec2(int x, int y)

        {
            this->x = x;
            this->y = y;
        }
        Vec2()
        {
            x = 0;
            y = 0;
        }
    };

    struct Node
    {
        Vec2 pos;
        int g = 0;
        int h = 0;
        int f = 0; //g+h
        Node* parent = NULL;
    };

public:


    AStar(int** board, int size);
    bool isPosValid(Vec2 pos);
    std::vector<Vec2> getAdjacentPos(Vec2 pos);
    void tryAddToOpen(Vec2 pos, int g, int h, Node* parent);
    std::vector<Node*> calculatePath(Vec2 startPos, Vec2 endPos);
    void calculate(Vec2 startPos, Vec2 endPos);
    std::vector<Node*> getPath();
    Node* popBestNode();
};