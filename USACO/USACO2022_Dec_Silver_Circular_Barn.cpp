#include <bits/stdc++.h>
using namespace std;

const int mx = 1e7;
vector<bool> p(mx, 1);
set<int> pr;

void solve() {
    int n, a = 0, b = 0, mn = 1e9;
    cin >> n;
    vector<int> v(n);
    vector<pair<int, int>> ans(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n; i++) {
        if (v[i] % 4 == 0) {
            ans[i].first = v[i] / 4 + 1;
            ans[i].second = 2;
        } else {
            if (v[i] % 2 == 0) {
                ans[i].first = ceil(v[i] / 4.0);
                ans[i].second = 1;
            } else {
                auto it = pr.upper_bound(v[i]);
                it--;
                for (; it != pr.begin(); it--) {
                    if ((v[i] - *it) % 4 == 0) break;
                }
                if ((*it) == v[i]) {
                    ans[i] = {1, 1};
                } else {
                    ans[i] = {1 + ceil((v[i] - (*it)) / 4.0), 1};
                }
            }
        }
    }
    for (int i = 0; i < n; i++) mn = min(mn, ans[i].first);
    for (int i = 0; i < n; i++) {
        if (mn == ans[i].first) {
            if (ans[i].second == 1) {
                cout << "Farmer John\n";
            } else cout << "Farmer Nhoj\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    p[0] = 0;
    pr.insert(1);
    for (int i = 2; i <= mx; i++) {
        if (p[i]) {
            pr.insert(i);
            for (int j = 2 * i; j <= mx; j += i) {
                p[j] = 0;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
