#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), index(n + 1);
    vector<long long> pre(n + 1), pre2(n + 1);
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) cin >> a[i], v[i] = {a[i], i + 1};
    sort(a.begin(), a.end());
    sort(v.begin(), v.end());
    for (int j = 0; j < n; j++) index[v[j].second] = j + 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (long long) i * a[i - 1];
        pre2[i] = pre2[i - 1] + a[i - 1];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int id, val;
        cin >> id >> val;
        if (n == 1) {
            cout << val << '\n';
            continue;
        }
        int prev_idx = index[id];
        auto it = upper_bound(a.begin(), a.end(), val);
        int new_idx = 1 + (it - a.begin());
        if (new_idx <= prev_idx) {
            cout << pre[prev_idx - 1] + pre2[prev_idx - 1] - pre2[new_idx - 1] + pre[n] - pre[prev_idx] + (long long) new_idx * val << '\n';
        } else {
            --new_idx;
            cout << pre[new_idx] - pre[prev_idx] - (pre2[new_idx] - pre2[prev_idx]) + pre[n] - pre[new_idx] + pre[prev_idx - 1] + (long long) new_idx * val << '\n';
        }
    }
}
