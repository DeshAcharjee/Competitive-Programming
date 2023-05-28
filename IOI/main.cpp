#include "game.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> c;
int N;

void initialize(int n) {
    N = n, c.resize(n);
}

int hasEdge(int u, int v) {
    return ++c[min(u, v)] == N - min(u, v) - 1;
}
