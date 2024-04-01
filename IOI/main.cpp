#include <bits/stdc++.h>

using namespace std;

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        g[u[i]].push_back(v[i]);
        g[v[i]].push_back(u[i]);
    }
    vector<int> in(n), en(n), d(n);
    int t = 0;
    auto dfs = [&](const auto &self, int u) -> void {
        in[u] = t++;
        for (int v : g[u]) {
            g[v].erase(find(g[v].begin(), g[v].end(), u));
            d[v] = d[u] + 1;
            self(self, v);
        }
        en[u] = t++;
    };
    dfs(dfs, 0);
    vector<int> id(n), ids;
    for (int i = 0; i < n; i++) {
        if (d[i] % 2 == 0) {
            id[i] = in[i];
        } else {
            id[i] = en[i];
        }
        ids.push_back(id[i]);
    }
    sort(ids.begin(), ids.end());
    for (int i = 0; i < n; i++) {
        id[i] = lower_bound(ids.begin(), ids.end(), id[i]) - ids.begin();
    }
    return id;
}

int find_next_station(int s, int t, vector<int> c) {
    if (c[0] > s) {
        int in = s + 1;
        for (int i = 0; i < c.size() - 1; i++) {
            if (in <= t && t <= c[i]) {
                return c[i];
            }
            in = c[i] + 1;
        }
        return c.back();
    } else {
        int en = s;
        for (int i = c.size() - 1; i > 0; i--) {
            if (c[i] <= t && t <= en) {
                return c[i];
            }
            en = c[i] - 1;
        }
        return c[0];
    }
}
