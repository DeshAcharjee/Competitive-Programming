#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
vector<long long> d, mn;
vector<int> dep, out, sz, par, euler;
vector<bool> centroid;
vector<vector<pair<int, int>>> g;

void dfs(int u, int p) {
    out[u] = euler.size();
    euler.push_back(u);
    for (auto [v, w] : g[u])
        if (v ^ p) {
            d[v] = d[u] + w;
            dep[v] = dep[u] + 1;
            dfs(v, u);
            out[u] = euler.size();
            euler.push_back(u);
        }
}

struct RMQ {
    vector<vector<int>> sparse;
    vector<int> lg;
    int comp(const int &a, const int &b) {
        return dep[a] < dep[b] ? a : b;
    }
    void init(const vector<int> &v) {
        int n = v.size();
        lg.resize(n + 1);
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        sparse = vector<vector<int>> (lg[n] + 1, vector<int> (n));
        for (int i = 0; i < n; i++) sparse[0][i] = v[i];
        for (int i = 1; i <= lg[n]; i++)
            for (int j = 0; j + (1 << (i - 1)) < n; j++)
                sparse[i][j] = comp(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
    }
    int query(int l, int r) {
        return comp(sparse[lg[r - l + 1]][l], sparse[lg[r - l + 1]][r - (1 << lg[r - l + 1]) + 1]);
    }
} rmq;

int lca(int u, int v) {
    if (out[u] > out[v]) swap(u, v);
    return rmq.query(out[u], out[v]);
}

long long dist(int u, int v) {
    return d[u] + d[v] - (d[lca(u, v)] << 1);
}

int findcentroid(int u, int p, int root) {
    for (auto [v, w] : g[u])
        if (v ^ p && !centroid[v] && sz[v] << 1 > sz[root])
            return findcentroid(v, u, root);
    return u;
}

void calcsz(int u, int p) {
    sz[u] = 1;
    for (auto [v, w] : g[u])
        if (v ^ p && !centroid[v])
            calcsz(v, u), sz[u] += sz[v];
}

int centroid_decompose(int u) {
    calcsz(u, u);
    int x = findcentroid(u, u, u);
    centroid[x] = 1;
    for (auto [v, w] : g[x])
        if (!centroid[v])
            par[centroid_decompose(v)] = x;
    return x;
}

void update(int u) {
    int x = u;
    while (u != -1) {
        mn[u] = min(mn[u], dist(x, u));
        u = par[u];
    }
}

void reset(int u) {
    while (u != -1) {
        mn[u] = INF;
        u = par[u];
    }
}

long long qry(int u) {
    int x = u;
    long long ret = INF;
    while (u != -1) {
        ret = min(ret, mn[u] + dist(x, u));
        u = par[u];
    }
    return ret;
}

void Init(int n, int a[], int b[], int c[]) {
    g.resize(n), d.resize(n), dep.resize(n), sz.resize(n), par.resize(n, -1), mn.resize(n, INF), centroid.resize(n), out.resize(n);
    for (int i = 0; i < n - 1; i++) {
        g[a[i]].push_back({b[i], c[i]});
        g[b[i]].push_back({a[i], c[i]});
    }
    dfs(0, 0);
    rmq.init(euler);
    centroid_decompose(0);
}

long long Query(int s, int x[], int t, int y[]) {
    for (int i = 0; i < s; i++) update(x[i]);
    long long ans = INF;
    for (int i = 0; i < t; i++) ans = min(ans, qry(y[i]));
    for (int i = 0; i < s; i++)
        if (mn[x[i]] != INF) reset(x[i]);
    return ans;
}
