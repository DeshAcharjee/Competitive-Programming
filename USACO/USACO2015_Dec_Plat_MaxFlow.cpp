#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> chains, in, dep, sz, par, topofchain, euler, out, diff;

struct RMQ {
    vector<vector<int>> sparse;
    vector<int> lg, pw;
    int sz;
    int comp(int a, int b) {
        return dep[a] < dep[b] ? a : b;
    }
    void init(vector<int> v) {
        sz = v.size();
        lg.resize(sz + 1);
        for (int i = 2; i <= sz; i++)
            lg[i] = lg[i >> 1] + 1;
        pw.resize(lg[sz] + 1);
        for (int i = 0; i <= lg[sz]; i++)
            pw[i] = (1 << i);
        sparse = vector<vector<int>> (sz, vector<int> (lg[sz] + 1));
        for (int i = 0; i < sz; i++) sparse[i][0] = v[i];
        for (int j = 1; j <= lg[sz]; j++)
            for (int i = 0; i + pw[j - 1] < sz; i++)
                sparse[i][j] = comp(sparse[i][j - 1], sparse[i + pw[j - 1]][j - 1]);
    }
    int query(int l, int r) {
        return comp(sparse[l][lg[r - l + 1]], sparse[r - pw[lg[r - l + 1]] + 1][lg[r - l + 1]]);
    }
} LCA;

int getlca(int a, int b) {
    if (out[a] > out[b]) swap(a, b);
    return LCA.query(out[a], out[b]);
}

void dfs(int u) {
    sz[u] = 1;
    out[u] = euler.size();
    euler.push_back(u);
    for (int v : g[u]) {
        if (v ^ par[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
            out[u] = euler.size();
            euler.push_back(u);
            sz[u] += sz[v];
        }
    }
}

void dfs_hld(int u, int top) {
    topofchain[u] = top;
    in[u] = chains.size();
    chains.push_back(u);
    int mx = 0, mxv = -1;
    for (int v : g[u]) {
        if (v ^ par[u]) {
            if (sz[v] > mx) {
                mx = sz[v];
                mxv = v;
            }
        }
    }
    if (mx) dfs_hld(mxv, top);
    for (int v : g[u]) {
        if (v != par[u] && v != mxv) {
            dfs_hld(v, v);
        }
    }
}

void pathupd(int a, int b) {
    while (a ^ b) {
        int top = topofchain[a];
        if (dep[top] <= dep[b]) {
            ++diff[in[b] + 1], --diff[in[a] + 1];
            return;
        } else {
            ++diff[in[top]], --diff[in[a] + 1];
            a = par[top];
        }
    }
}

void upd(int a, int b) {
    int lca = getlca(a, b);
    pathupd(a, lca);
    pathupd(b, lca);
    ++diff[in[lca]], --diff[in[lca] + 1];
}

int main() {
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    g.resize(n), dep.resize(n), sz.resize(n), in.resize(n), out.resize(n), par.resize(n), topofchain.resize(n), diff.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0);
    dfs_hld(0, 0);
    LCA.init(euler);
    while (m--) {
        int a, b;
        cin >> a >> b;
        upd(--a, --b);
    }
    vector<int> pre(n);
    pre[0] = diff[0];
    for (int i = 1; i < n; i++) pre[i] = diff[i] + pre[i - 1];
    cout << *max_element(pre.begin(), pre.end()) << '\n';
}
