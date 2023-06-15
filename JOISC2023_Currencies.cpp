#include <bits/stdc++.h>
using namespace std;

struct fenwick {
    vector<pair<long long, int>> fenw;
    int n;
    fenwick(int n_) : n(n_) {
        fenw.resize(n, {0, 0});
    }
    void upd(int i, int d, int d2) {
        for (; i < n; i |= i + 1) fenw[i].first += d, fenw[i].second += d2;
    }
    pair<long long, int> qry(int i) {
        pair<long long, int> s = {0, 0};
        for (; i >= 0; i = (i & (i + 1)) - 1) s.first += fenw[i].first, s.second += fenw[i].second;
        return s;
    }
};

vector<vector<int>> g, up;
vector<int> in, out, dep;
int t;
const int lg = 17;

void dfs(int u) {
    in[u] = t++;
    for (int i = 1; i < lg; i++) up[i][u] = up[i - 1][up[i - 1][u]];
    for (int v : g[u])
        if (v ^ up[0][u])
            up[0][v] = u, dep[v] = dep[u] + 1, dfs(v);
    out[u] = t;
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
    int n, m, q, c = 0;
    cin >> n >> m >> q;
    up = vector<vector<int>> (lg, vector<int> (n)), g.resize(n), in.resize(n), out.resize(n), dep.resize(n);
    vector<pair<int, int>> e(n - 1);
    for (auto &[a, b] : e) {
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    for (auto &[a, b] : e)
        if (b == up[0][a])
            swap(a, b);
    vector<pair<int, int>> ck(m);
    for (auto &[c, p] : ck) cin >> p >> c, --p;
    sort(ck.begin(), ck.end());
    fenwick fen(n);
    vector<vector<int>> v(m);
    vector<tuple<int, int, int, long long>> qr(q);
    vector<int> l(q), r(q, m - 1), ans(q);
    for (int i = 0; i < q; i++) {
        v[(m - 1) >> 1].push_back(i);
        auto &[s, t, x, y] = qr[i];
        cin >> s >> t >> x >> y, --s, --t;
    }
    for (int itr = 0; itr < lg; itr++) {
        for (int i = 0; i < m; i++) {
            auto [c, p] = ck[i];
            int b = e[p].second;
            fen.upd(in[b], c, 1);
            fen.upd(out[b], -c, -1);
            for (int id : v[i]) {
                auto [s, t, x, y] = qr[id];
                auto [s1, s2, s3] = make_tuple(fen.qry(in[s]), fen.qry(in[t]), fen.qry(in[lca(s, t)]));
                if (s1.first + s2.first - (s3.first << 1) > y) r[id] = i - 1;
                else ans[id] = s1.second + s2.second - (s3.second << 1), l[id] = i + 1;
                int m = l[id] + r[id] >> 1;
                if (i ^ m && l[id] <= r[id]) v[m].push_back(id);
            }
            v[i].clear();
        }
        if (itr < lg - 1)
            for (int i = 0; i < n; i++) fen.fenw[i] = {0, 0};
    }
    for (int i = 0; i < q; i++) {
        auto [s, t, x, y] = qr[i];
        ans[i] = fen.qry(in[s]).second + fen.qry(in[t]).second - (fen.qry(in[lca(s, t)]).second << 1) - ans[i];
        cout << max(x - ans[i], -1) << '\n';
    }
}
