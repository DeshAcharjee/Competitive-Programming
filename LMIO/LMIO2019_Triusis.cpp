#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, ans = 0;
    cin >> n >> m;
    vector<int> a(n), b;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] <= (i + 1) * m) {
            b.push_back((i + 1) * m - a[i]);
        }
    }
    vector<int> lis;
    for (int x : b) {
        auto it = upper_bound(lis.begin(), lis.end(), x);
        if (it == lis.end()) lis.push_back(x);
        else *it = x;
    }
    cout << n - lis.size() << '\n';
    return 0;
}
