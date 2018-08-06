/* Your code here! */
#include "dsets.h"

DisjointSets::DisjointSets() {
    father.clear();
    ssf.clear();
}

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        father.push_back(-1);
        ssf.push_back(1);
    }
}

int DisjointSets::find(int x) {
    return father[x] < 0 ? x : find(father[x]);
}

void DisjointSets::setunion(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (ssf[a] >= ssf[b]) {
        father[b] = a;
        ssf[a] += ssf[b];
    } else {
        father[a] = b;
        ssf[b] += ssf[a];
    }
}