#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<long long> p(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int tz = __builtin_ctz(a[i]);
        p[i + 1] = p[i] + (1 << tz);
        a[i] >>= tz;
    }
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        cout << a[lower_bound(p.begin(), p.end(), x) - p.begin() - 1] << '\n';
    }
}
