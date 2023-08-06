#include <bits/stdc++.h>

using namespace std;

const int N = 2e5, lg = 18;
vector<int> g[N];
int d[N], up[lg][N];

void dfs(int u) {
    for (int i = 1; i < lg; i++) {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int v : g[u]) {
        if (v ^ up[0][u]) {
            d[v] = d[u] + 1;
            up[0][v] = u;
            dfs(v);
        }
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int k = d[u] - d[v];
    for (int i = 0; i < lg; i++) {
        if (k >> i & 1) {
            u = up[i][u];
        }
    }
    if (u == v) return u;
    for (int i = lg - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0);
    vector<int> a(m);
    vector<set<int>> oc(n), oc2(n);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        --a[i];
        oc2[a[i]].insert(i);
    }
    for (int i = 0; i < m - 1; i++) {
        oc[lca(a[i], a[i + 1])].insert(i);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int pos, v;
            cin >> pos >> v;
            --pos, --v;
            if (pos) {
                oc[lca(a[pos - 1], a[pos])].erase(pos - 1);
            }
            if (pos != m - 1) {
                oc[lca(a[pos], a[pos + 1])].erase(pos);
            }
            oc2[a[pos]].erase(pos);
            a[pos] = v;
            oc2[a[pos]].insert(pos);
            if (pos) {
                oc[lca(a[pos - 1], a[pos])].insert(pos - 1);
            }
            if (pos != m - 1) {
                oc[lca(a[pos], a[pos + 1])].insert(pos);
            }
        } else {
            int l, r, v;
            cin >> l >> r >> v;
            --l, --r, --v;
            auto it2 = oc2[v].lower_bound(l);
            if (it2 != oc2[v].end()) {
                int x = *it2;
                if (x <= r) {
                    cout << x + 1 << ' ' << x + 1 << '\n';
                    continue;
                }
            }
            auto it = oc[v].lower_bound(l);
            if (it == oc[v].end()) {
                cout << "-1 -1\n";
            } else {
                int x = *it;
                if (x >= r) {
                    cout << "-1 -1\n";
                } else {
                    cout << x + 1 << ' ' << x + 2 << '\n';
                }
            }
        }
    }
    return 0;
}
