#include <bits/stdc++.h>
using namespace std;

const int MX = 51;
int dp[MX][MX][MX][MX];
int pre[MX][MX];

int calc_dp(int l1, int r1, int l2, int r2) {
    if (l1 == r1 && l2 == r2) return 0;
    if (dp[l1][r1][l2][r2]) return dp[l1][r1][l2][r2];
    int mn = 1e9;
    for (int i = l1; i < r1; i++)
        mn = min(mn, calc_dp(l1, i, l2, r2) + calc_dp(i + 1, r1, l2, r2));
    for (int i = l2; i < r2; i++)
        mn = min(mn, calc_dp(l1, r1, l2, i) + calc_dp(l1, r1, i + 1, r2));
    return dp[l1][r1][l2][r2] = mn + pre[r1][r2] - pre[r1][l2 - 1] - pre[l1 - 1][r2] + pre[l1 - 1][l2 - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    int r[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> r[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            pre[i][j] = pre[i][j - 1] + pre[i - 1][j] - pre[i - 1][j - 1] + r[i - 1][j - 1];
    cout << calc_dp(1, n, 1, m) << '\n';
}
