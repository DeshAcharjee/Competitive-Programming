#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> c(n);
    vector<vector<int>> g(n);
    vector f(1 << k, vector<long long> (n));
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        --c[i];
        ++f[1 << c[i]][i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    long long ans = 0;
    for (int i = 0; i < (1 << k); i++) {
        for (int u = 0; u < n; u++) {
            for (int v : g[u]) {
                if (i >> c[v] & 1 ^ 1) {
                    f[i | (1 << c[v])][v] += f[i][u];
                }
            }
            ans += f[i][u];
        }
    }
    cout << ans - n << '\n';
    return 0;
}
