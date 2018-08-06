/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>

#include "png.h"
#include "rgbapixel.h"
#include "dsets.h"

using namespace std;

class SquareMaze {
public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
private:
    int width;
    int height;
    DisjointSets dset;
    vector<bool> right;
    vector<bool> down;
    void dfs(int x, int y, int result);
    bool get_path(int x, int y, vector<int>& path);
    int *exit_point;
    int out_point;
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int wal[4][3] = {{0, 0, 0}, {0, 0, 1}, {-1, 0, 0}, {0, -1, 1}};
};

#endif