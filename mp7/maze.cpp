/* Your code here! */
#include "maze.h"
#include <ctime>

SquareMaze::SquareMaze() {}

void SquareMaze::makeMaze(int width, int height) {
    srand(time(NULL));
    this->width = width;
    this->height = height;
    dset.addelements(width * height);
    for (int i = 0; i < width * height; i++) {
        right.push_back(true);
        down.push_back(true);
    }
    for (int i = 0; i < width * height; i++) {
        vector<int> can_dir;
        int x = i % width;
        int y = i / width;
        int fai = dset.find(i);
        if (x != 0 && fai != dset.find(y*width+x-1)) {
            can_dir.push_back(0);
        }
        if (y != 0 && fai != dset.find((y-1)*width+x)) {
            can_dir.push_back(1);
        }
        if (x != width - 1 && fai != dset.find(y*width+x+1)) {
            can_dir.push_back(2);
        }
        if (y != height - 1 && fai != dset.find((y+1)*width+x)) {
            can_dir.push_back(3);
        }
        if (can_dir.size() == 0) continue;
        int dir = can_dir[rand() % can_dir.size()];
        switch (dir) {
            case 0:
                setWall(x-1, y, 0, false);
                dset.setunion(i, y*width+x-1);
                break;
            case 1:
                setWall(x, y-1, 1, false);
                dset.setunion(i, (y-1)*width+x);
                break;
            case 2:
                setWall(x, y, 0, false);
                dset.setunion(i, y*width+x+1);
                break;
            case 3:
                setWall(x, y, 1, false);
                dset.setunion(i, (y+1)*width+x);
                break;
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0 && x < width-1) {
        return !right[y*width+x];
    }
    if (dir == 1 && y < height-1) {
        return !down[y*width+x];
    }
    if (dir == 2 && x > 0) {
        return !right[y*width+x-1];
    }
    if (dir == 3 && y > 0) {
        return !down[(y-1)*width+x];
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) {
        if (x != width - 1) {
            right[y * width + x] = exists;
        }
    } else if (dir == 1) {
        if (y != height - 1) {
            down[y * width + x] = exists;
        }
    }
}

// int dis[1005][1005];

void SquareMaze::dfs(int x, int y, int result) {
    // dis[x][y] = result;
    if (y == height - 1) {
        exit_point[x] = result;
    }
    for (int i = 0; i < 4; i++) {
        if (canTravel(x, y, i)) {
            result++;
            setWall(x+wal[i][0], y+wal[i][1], wal[i][2], true);
            dfs(x+dir[i][0], y+dir[i][1], result);
            result--;
            setWall(x+wal[i][0], y+wal[i][1], wal[i][2], false);
        }
    }
}

bool SquareMaze::get_path(int x, int y, vector<int>& path) {
    if (x == out_point && y == height - 1) {
        return true;
    }
    for (int i = 0; i < 4; i++) {
        if (canTravel(x, y, i)) {
            path.push_back(i);
            setWall(x+wal[i][0], y+wal[i][1], wal[i][2], true);
            if (get_path(x+dir[i][0], y+dir[i][1], path)) {
                setWall(x+wal[i][0], y+wal[i][1], wal[i][2], false);
                return true;
            }
            path.pop_back();
            setWall(x+wal[i][0], y+wal[i][1], wal[i][2], false);
        }
    }
    return false;
}

vector<int> SquareMaze::solveMaze() {
    exit_point = new int[width + 5];
    // memset(dis, -1, sizeof(dis));
    dfs(0, 0, 0);
    out_point = 0;
    for (int i = 0; i < width; i++) {
        if (exit_point[i] > exit_point[out_point]) {
            out_point = i;
        }
    }
    // for (int i = 0; i < width; i++) {
    //     for (int j = 0; j < height; j++) {
    //         if (dis[i][j] < 0) {
    //             cout<<"Debug:"<<i<<" "<<j<<endl;
    //         }
    //     }
    // }
    vector<int> path;
    get_path(0, 0, path);
    delete exit_point;
    return path;
}

PNG* SquareMaze::drawMaze() const {
    PNG* output = new PNG(width * 10 + 1, height * 10 + 1);
    for (int i = 0; i < height * 10; i++) {
        (*output)(0, i)->red = 0;   
        (*output)(0, i)->green = 0; 
        (*output)(0, i)->blue = 0;
    }
    for (int i = 10; i < width * 10; i++) {
        (*output)(i, 0)->red = 0;   
        (*output)(i, 0)->green = 0; 
        (*output)(i, 0)->blue = 0;
    }
    for (int i = 0; i < width * height; i++) {
        int x = i % width;
        int y = i / width;
        if (right[i]) {
            for (int j = 0; j <= 10; j++) {
                (*output)((x + 1) * 10, y * 10 + j)->red = 0;
                (*output)((x + 1) * 10, y * 10 + j)->green = 0;
                (*output)((x + 1) * 10, y * 10 + j)->blue = 0;
            }
        }
        if (down[i]) {
            for (int j = 0; j <= 10; j++) {
                (*output)(x * 10 + j, (y + 1) * 10)->red = 0;
                (*output)(x * 10 + j, (y + 1) * 10)->green = 0;
                (*output)(x * 10 + j, (y + 1) * 10)->blue = 0;
            }
        }
    }
    // (*output)(width * 10, height * 10)->red = 0;
    // (*output)(width * 10, height * 10)->green = 0;
    // (*output)(width * 10, height * 10)->blue = 0;
    return output;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* maze = drawMaze();
    vector<int> path = solveMaze();
    int x = 5, y = 5;
    for (int i = 0; i < (int)path.size(); i++) {
        if (path[i] == 0) {
            for (int j = 0; j <= 10; j++) {
                (*maze)(x+j,y)->red = 255;
                (*maze)(x+j,y)->green = 0;
                (*maze)(x+j,y)->blue = 0;
            }
            x += 10;
        } else if (path[i] == 1) {
            for (int j = 0; j <= 10; j++) {
                (*maze)(x,y+j)->red = 255;
                (*maze)(x,y+j)->green = 0;
                (*maze)(x,y+j)->blue = 0;
            }
            y += 10;
        } else if (path[i] == 2) {
            for (int j = 0; j <= 10; j++) {
                (*maze)(x-j,y)->red = 255;
                (*maze)(x-j,y)->green = 0;
                (*maze)(x-j,y)->blue = 0;
            }
            x -= 10;
        } else if (path[i] == 3) {
            for (int j = 0; j <= 10; j++) {
                (*maze)(x,y-j)->green = 0;
                (*maze)(x,y-j)->red = 255;
                (*maze)(x,y-j)->blue = 0;
            }
            y -= 10;
        }
    }
    for (int i = 1; i < 10; i++) {
        (*maze)(out_point * 10 + i, height * 10)->red = 255;
        (*maze)(out_point * 10 + i, height * 10)->green = 255;
        (*maze)(out_point * 10 + i, height * 10)->blue = 255;
    }
    return maze;
}