#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, ans = 0;
    cin >> n >> m;
    vector<int> a(n), b;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++)
        if (a[i] <= (i + 1) * m)
            b.push_back((i + 1) * m - a[i]);
    multiset<int> lis;
    for (int x : b) {
        auto it = lis.upper_bound(x);
        if (it != lis.end()) lis.erase(it);
        lis.insert(x);
    }
    cout << n - lis.size() << '\n';
}
