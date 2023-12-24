#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> x(n);
    for (int &v : x) {
        cin >> v;
    }
    sort(x.begin(), x.end());
    vector<long long> p(n + 1);
    for (int i = 0; i < n; i++) {
        p[i + 1] = p[i] + x[i];
    }
    auto f = [&](int a, int b, int y) {
        int j = upper_bound(x.begin(), x.end(), y) - x.begin();
        return (long long) a * ((long long) j * y - p[j]) + (long long) b * (p[n] - p[j] - (long long) (n - j) * y);
    };
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        int l = 0, r = x.back();
        while (l < r) {
            int m = l + r >> 1;
            if (f(a, b, m) > f(a, b, m + 1)) l = m + 1;
            else r = m;
        }
        cout << f(a, b, l) << '\n';
    }
    return 0;
}