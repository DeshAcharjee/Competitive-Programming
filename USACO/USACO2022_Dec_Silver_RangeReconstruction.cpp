#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int r[n][n];
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            cin >> r[i][j];
    vector<int> a(n, 0);
    for (int i = 0; i < n - 1; i++) {
        bool f = 1;
        a[i + 1] = r[i][i + 1] - a[i];
        for (int j = 0; j <= i; j++) {
            int mx = *max_element(a.begin() + j, a.begin() + i + 2);
            int mn = *min_element(a.begin() + j, a.begin() + i + 2);
            if (mx - mn != r[j][i + 1]) {
                f = 0;
                break;
            }
        }
        if (!f) {
            f = 1;
            a[i + 1] = a[i] - r[i][i + 1];
            for (int j = 0; j <= i; j++) {
                int mx = *max_element(a.begin() + j, a.begin() + i + 2);
                int mn = *min_element(a.begin() + j, a.begin() + i + 2);
                if (mx - mn != r[j][i + 1]) {
                    f = 0;
                    break;
                }
            }
        }
        if (!f) {
            f = 1;
            a[i + 1] = a[i];
            for (int j = 0; j <= i; j++) {
                int mx = *max_element(a.begin() + j, a.begin() + i + 2);
                int mn = *min_element(a.begin() + j, a.begin() + i + 2);
                if (mx - mn != r[j][i + 1]) {
                    f = 0;
                    break;
                }
            }
        }
        if (!f) a[i + 1] = a[i] + r[i][i + 1];
    }
    for (int i = 0; i < n; i++) {
        cout << a[i];
        if (i < n - 1) cout << ' ';
    }
}
