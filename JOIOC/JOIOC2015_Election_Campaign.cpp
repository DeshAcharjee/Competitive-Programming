#include <bits/stdc++.h>
using namespace std;

vector<int> in, out, dep, dp, dp2;
vector<vector<int>> g, up;
vector<vector<tuple<int, int, int>>> qr;
int t, lg;

struct fenwick {
    vector<int> fenw;
    int n;
    void init(int n_) {
        fenw.resize(n = n_);
    }
    void upd(int u, int x) {
        for (; u < n; u |= u + 1) fenw[u] += x;
    }
    int qry(int u) {
        int s = 0;
        for (; u >= 0; u = (u & (u + 1)) - 1) s += fenw[u];
        return s;
    }
    int qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
} fen;

void dfs(int u) {
    in[u] = t++;
    for (int i = 1; i < lg; i++) up[i][u] = up[i - 1][up[i - 1][u]];
    for (int v : g[u])
        if (v ^ up[0][u])
            dep[v] = dep[u] + 1, up[0][v] = u, dfs(v);
    out[u] = t++;
}

void calc_dp(int u, int p) {
    for (int v : g[u])
        if (v ^ p) {
            calc_dp(v, u);
            dp2[u] += dp[v];
        }
    dp[u] = dp2[u];
    for (auto [x, y, w] : qr[u]) {
        int cost = dp2[u] - fen.qry(in[u], in[x]) - fen.qry(in[u], in[y]);
        dp[u] = max(dp[u], cost + w);
    }
    fen.upd(in[u], dp[u] - dp2[u]);
    fen.upd(out[u], dp2[u] - dp[u]);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = dep[u] - dep[v];
    for (int i = 0; i < lg; i++)
        if (k >> i & 1)
            u = up[i][u];
    if (u == v) return u;
    for (int i = lg - 1; i >= 0; i--)
        if (up[i][u] ^ up[i][v])
            u = up[i][u], v = up[i][v];
    return up[0][u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    while ((1 << lg) <= n) ++lg;
    g.resize(n), up = vector<vector<int>> (lg, vector<int> (n)), dp.resize(n), dp2.resize(n), dep.resize(n), qr.resize(n), in.resize(n), out.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0);
    fen.init(t);
    int q;
    cin >> q;
    while (q--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        qr[lca(u, v)].push_back({u, v, w});
    }
    calc_dp(0, 0);
    cout << dp[0] << '\n';
}
