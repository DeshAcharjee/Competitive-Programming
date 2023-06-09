#include "race.h"
#include <bits/stdc++.h>
using namespace std;
 
const int INF = 1E9;
int k, ans = INF;
vector<vector<pair<int, int>>> g;
vector<int> sz, dep, to, ds;
vector<bool> centroid;
 
void calc(int u, int p) {
    sz[u] = 1;
    for (auto [v, w] : g[u])
        if (v ^ p && !centroid[v])
            calc(v, u), sz[u] += sz[v];
}
 
int findcentroid(int u, int p, const int &s) {
    for (auto [v, w] : g[u])
        if (v ^ p && !centroid[v] && sz[v] > s)
            return findcentroid(v, u, s);
    return u;
}
 
void calcdep(int u, int p, int d) {
    dep[u] = d;
    for (auto [v, w] : g[u])
        if (v ^ p && !centroid[v])
            calcdep(v, u, d + 1);
}
 
void addmx(int u, int p, int length) {
    if (length > k) return;
    ds[length] = min(ds[length], dep[u]);
    to.push_back(length);
    for (auto [v, w] : g[u])
        if (v ^ p && !centroid[v])
            addmx(v, u, length + w);
}
 
void calcmx(int u, int p, int length) {
    if (length > k) return;
    ans = min(ans, dep[u] + ds[k - length]);
    for (auto [v, w] : g[u])
        if (v ^ p && !centroid[v])
            calcmx(v, u, length + w);
}
 
void decompose(int u) {
    calc(u, u);
    int x = findcentroid(u, u, sz[u] >> 1);
    calcdep(x, x, 0);
    centroid[x] = 1;
    for (auto [v, w] : g[x]) {
        if (!centroid[v]) {
            calcmx(v, x, w);
            addmx(v, x, w);
        }
    }
    ans = min(ans, ds[k]);
    for (int i : to) ds[i] = INF;
    to.clear();
    for (auto [v, w] : g[x])
        if (!centroid[v])
            decompose(v);
}
 
int best_path(int n, int k_, int h[][2], int l[]) {
    k = k_;
    g = vector<vector<pair<int, int>>> (n), centroid = vector<bool> (n), dep = vector<int> (n), ds = vector<int>(k + 1, INF), sz = dep;
    for (int i = 0; i < n - 1; i++) {
        int u = h[i][0], v = h[i][1], w = l[i];
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    decompose(0);
    return ans == INF ? -1 : ans;
}
