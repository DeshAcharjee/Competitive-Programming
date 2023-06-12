#include <bits/stdc++.h>
using namespace std;

vector<int> coin_flips(vector<int> b, int c) {
    int xr = 0;
    for (int i = 0; i < 64; i++) xr ^= i * b[i];
    return vector<int> (1, xr ^ c);
}

int find_coin(vector<int> b) {
    int xr = 0;
    for (int i = 0; i < 64; i++) xr ^= i * b[i];
    return xr;
}
