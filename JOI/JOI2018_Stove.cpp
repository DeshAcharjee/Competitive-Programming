#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> t(n), diff(n - 1);
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < n - 1; i++) diff[i] = t[i + 1] - t[i];
    sort(diff.begin(), diff.end());
    cout << accumulate(diff.begin(), diff.begin() + n - k, 0LL) + k << '\n';
}
