#include "dreaming.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> g;
vector<bool> vis;
vector<int> dd;
int ans, ld;

void calcd(int u, int p, int d_, vector<pair<int, int>> &a) {
    vis[u] = 1;
    a.push_back({u, d_});
    for (auto [v, w] : g[u])
        if (v ^ p)
            calcd(v, u, d_ + w, a);
}

void getmax(int x) {
    vector<pair<int, int>> d, d2;
    calcd(x, x, 0, d);
    int mx = -1, mxn;
    for (auto [a, b] : d)
        if (b > mx) mx = b, mxn = a;
    d.clear();
    calcd(mxn, mxn, 0, d);
    int mx2 = -1, mxn2;
    for (auto [a, b] : d) {
        dd[a] = b;
        if (b > mx2) mx2 = b, mxn2 = a;
    }
    ld = max(ld, mx2);
    calcd(mxn2, mxn2, 0, d2);
    for (auto [a, b] : d2)
        ans = min(ans, max(b, dd[a]));
}

int travelTime(int n, int m, int l, int a[], int b[], int t[]) {
    g.resize(n), dd.resize(n), vis.resize(n);
    for (int i = 0; i < m; i++) {
        int u = a[i], v = b[i], w = t[i];
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector<int> mx;
    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            ans = 2e9;
            getmax(i);
            mx.push_back(ans);
        }
    sort(mx.rbegin(), mx.rend());
    return max(ld, mx.size() == 1 ? mx[0] : mx.size() == 2 ? mx[0] + mx[1] + l : max(mx[0] + mx[1] + l, mx[1] + mx[2] + 2 * l));
}
