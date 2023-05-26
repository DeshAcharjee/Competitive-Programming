#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k, ans = INF;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = s[i] == 'J' ? 0 : s[i] == 'O' ? 1 : 2;
    vector<vector<int>> p(3, vector<int> (n + 1));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < n; j++)
            p[i][j + 1] = p[i][j] + (v[j] == i);
    for (int i = 0; i < n; i++) {
        if (v[i] == 0) {
            int s = i;
            for (int j = 0; j < 3; j++) {
                if (p[j][n] - p[j][s] < k) break;
                int l = s + 1, r = n;
                while (l < r) {
                    int m = l + r >> 1;
                    if (p[j][m] - p[j][s] < k) l = m + 1;
                    else r = m;
                }
                s = l;
                if (j == 2) ans = min(ans, s - i);
            }
        }
    }
    cout << (ans == INF ? -1 : ans - 3 * k) << '\n';
}
