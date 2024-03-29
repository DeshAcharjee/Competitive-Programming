#include <bits/stdc++.h>

using namespace std;

const int MX = 51;
int dp[MX][MX][MX][MX];
int p[MX][MX];

int calc_dp(int l1, int r1, int l2, int r2) {
    if (l1 == r1 && l2 == r2) return 0;
    if (dp[l1][r1][l2][r2]) return dp[l1][r1][l2][r2];
    int mn = 1e9;
    for (int i = l1; i < r1; i++) {
        mn = min(mn, calc_dp(l1, i, l2, r2) + calc_dp(i + 1, r1, l2, r2));
    }
    for (int i = l2; i < r2; i++) {
        mn = min(mn, calc_dp(l1, r1, l2, i) + calc_dp(l1, r1, i + 1, r2));
    }
    return dp[l1][r1][l2][r2] = mn + p[r1][r2] - p[r1][l2 - 1] - p[l1 - 1][r2] + p[l1 - 1][l2 - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> p[i][j];
            p[i][j] += p[i][j - 1] + p[i - 1][j] - p[i - 1][j - 1];
        }
    }
    cout << calc_dp(1, n, 1, m) << '\n';
    return 0;
}
