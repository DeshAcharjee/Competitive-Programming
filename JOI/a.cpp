#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int &x : a) {
        cin >> x;
    }
    for (int &x : b) {
        cin >> x;
    }
    auto check = [&](long long x) {
        __int128 t = 0;
        for (int i = 0; i < n; i++) {
            if (b[i] >= a[i]) {
                t += m - (x + b[i] - 1) / b[i];
            } else {
                if ((long long) a[i] * m >= x) t += m - (x + a[i] - 1) / a[i];
                else t -= (x - (long long) a[i] * m + b[i] - 1) / b[i];
            }
        }
        return t >= 0;
    };
    long long l = 0, r = 1e18;
    while (l < r) {
        long long m = l + r + 1 >> 1;
        if (check(m)) l = m;
        else r = m - 1;
    }
    cout << l << '\n';
    return 0;
}