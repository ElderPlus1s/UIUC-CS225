/* Your code here! */
#ifndef DSETS_H
#define DSETS_H
#include <vector>

using namespace std;

class DisjointSets {
public:
    DisjointSets();
    void addelements(int num);
    int find (int x);
    void setunion(int a, int b);
private:
    vector<int> father;
    vector<int> ssf;
};

#endif