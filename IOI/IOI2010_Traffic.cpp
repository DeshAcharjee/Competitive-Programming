#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> sz, a;
int ans = INT_MAX, mn;

void dfs(int u, int p) {
    sz[u] = a[u];
    for (int v : g[u])
        if (v ^ p)
            dfs(v, u), sz[u] += sz[v];
}

void solve(int u, int p) {
    int x = sz[0] - sz[u];
    for (int v : g[u])
        if (v ^ p)
            solve(v, u), x = max(x, sz[v]);
    if (ans > x) ans = x, mn = u;
}

int LocateCentre(int n, int p[], int s[], int d[]) {
    g.resize(n), sz.resize(n), a.resize(n);
    for (int i = 0; i < n; i++) a[i] = p[i];
    for (int i = 0; i < n - 1; i++) {
        g[s[i]].push_back(d[i]);
        g[d[i]].push_back(s[i]);
    }
    dfs(0, 0);
    solve(0, 0);
    return mn;
}
