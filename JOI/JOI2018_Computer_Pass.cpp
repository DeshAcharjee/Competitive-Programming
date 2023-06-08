#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
vector<vector<pair<int, int>>> g;

void djikstra(int src, vector<long long> &sp) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    sp[src] = 0;
    pq.push({0, src});
    while (pq.size()) {
        int u = pq.top().second;
        pq.pop();
        for (auto [v, w] : g[u])
            if (sp[v] > sp[u] + w)
                sp[v] = sp[u] + w, pq.push({sp[v], v});
    }
}

int S, T, U, V;
vector<vector<long long>> sp;
vector<long long> dp1, dp2;
long long ans = INF;

long long calc_dp1(int u, long long s) {
    if (s + sp[1][u] > sp[0][T]) return INF;
    if (dp1[u] != -1) return dp1[u];
    long long mn = sp[3][u];
    for (auto [v, w] : g[u]) mn = min(mn, calc_dp1(v, s + w));
    ans = min(ans, sp[2][u] + mn);
    return dp1[u] = mn;
}

long long calc_dp2(int u, long long s) {
    if (s + sp[1][u] > sp[0][T]) return INF;
    if (dp2[u] != -1) return dp2[u];
    long long mn = sp[2][u];
    for (auto [v, w] : g[u]) mn = min(mn, calc_dp2(v, s + w));
    ans = min(ans, sp[3][u] + mn);
    return dp2[u] = mn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m >> S >> T >> U >> V;
    --S, --T, --U, --V, g.resize(n), sp = vector<vector<long long>> (4, vector<long long> (n, INF)), dp1 = dp2 = vector<long long> (n, -1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    djikstra(S, sp[0]), djikstra(T, sp[1]), djikstra(U, sp[2]), djikstra(V, sp[3]);
    calc_dp1(S, 0), calc_dp2(S, 0);
    cout << min(ans, sp[2][V]) << '\n';
}
