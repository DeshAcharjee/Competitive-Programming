#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector r(n, vector<int> (n)), e = r;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; j < n - i; j++) {
            char c;
            cin >> c;
            r[i][i + j] = c - '0';
        }
    }
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            e[i][j] = r[i][j];
            for (int k = i + 1; k < j; k++) {
                e[i][j] ^= (r[i][k] & e[k][j]);
            }
            ans += e[i][j];
        }
    }
    cout << ans << '\n';
    return 0;
}