#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;
vector<int> g[N];
string s;
int dp[2][N];

void dfs(int u, int p) {
    dp[0][u] = dp[1][u] = s[u];
    int sum_dp = 0, mx_dp = 0;
    for (int v : g[u]) {
        if (v != p) {
            dfs(v, u);
            dp[0][u] = max(dp[0][u], dp[0][v]);
            sum_dp += dp[1][v];
            mx_dp = max(mx_dp, dp[1][v]);
        }
    }
    dp[0][u] = max({dp[0][u], sum_dp - s[u], mx_dp + s[u]});
    dp[1][u] = max(dp[1][u], sum_dp - s[u]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[--a].push_back(--b);
        g[b].push_back(a);
    }
    cin >> s;
    for (char &c : s) c -= '0';
    dfs(0, 0);
    cout << dp[0][0] << '\n';
    return 0;
}
