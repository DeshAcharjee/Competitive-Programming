#include <bits/stdc++.h>

using namespace std;

struct Info {
    int length;
    long long sum;
    int hash;
    int label;
};

const int N = 2e5 + 1, lg = 18, M = 1e9 + 7, B = 37;
vector<pair<int, int>> g[N];
Info dp[N];
bitset<N> vis;
int nxt[lg][N], pwr[N];

void dfs(int u) {
    vis[u] = 1;
    if (!g[u].size()) return;
    int x = g[u][0].first, first = g[u][0].second;
    for (auto [v, w] : g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
        if (make_pair(dp[v].length, -w) > make_pair(dp[x].length, -first) || x == v) {
            x = v;
            first = w;
        } else if (make_pair(dp[v].length, -w) == make_pair(dp[x].length, -first)) {
            int curhash1 = dp[x].hash, curhash2 = dp[v].hash;
            int z = x, r = v;
            for (int i = lg - 1; i >= 0; i--) {
                if (!nxt[i][v]) continue;
                if (curhash1 - dp[nxt[i][z]].hash == curhash2 - dp[nxt[i][v]].hash) {
                    z = nxt[i][z];
                    v = nxt[i][v];
                }
            }
            if (nxt[0][z] && dp[z].label > dp[v].label) {
                 x = r;
            }
        }
    }
    dp[u] = {dp[x].length + 1, dp[x].sum + first, (dp[x].hash + (long long) first * pwr[dp[x].length]) % M, first};
    nxt[0][u] = x;
    for (int i = 1; i < lg; i++) {
        nxt[i][u] = nxt[i - 1][nxt[i - 1][u]];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    pwr[0] = 1;
    for (int i = 1; i < N; i++) {
        pwr[i] = (long long) pwr[i - 1] * B % M;
    }
    int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b, l;
        cin >> a >> b >> l;
        g[a].push_back({b, l});
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dp[i].length << ' ' << dp[i].sum << '\n';
    }
    return 0;
}
