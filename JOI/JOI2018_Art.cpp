#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<long long, int>> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());
    vector<long long> pre(n + 1);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + v[i].second, pre[i] -= v[i].first;
    long long ans = 0, mn = pre[0];
    for (int i = 1; i <= n; i++) {
        ans = max(ans, pre[i] - mn + (i == n ? 0 : v[i].first) - v[i - 1].first);
        mn = min(mn, pre[i]);
    }
    cout << ans << '\n';
}
