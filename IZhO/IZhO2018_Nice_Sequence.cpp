#include <bits/stdc++.h>

using namespace std;

const int N = 4e5;
int n, m, T, K, a[N];
bool vis[N];

void dfs(int u) {
    if (u < 0 || u > K || vis[u]) return;
    vis[u] = true;
    dfs(u + n);
    dfs(u - m);
    a[u] = T++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        K = n + m - gcd(n, m) - 1, T = 0;
        cout << K << '\n';
        for (int i = 0; i <= K; i++) vis[i] = false;
        for (int i = 0; i <= K; i++) {
            dfs(i);
            if (i) cout << a[i] - a[i - 1] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
