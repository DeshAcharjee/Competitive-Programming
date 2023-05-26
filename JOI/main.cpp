#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n + 1);
    vector<int> b(n), p(n), s(n), x(n + 1);
    for (int i = 0; i <= n; i++) cin >> a[i].first, a[i].second = i;
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    p[0] = max(0, a[0].first - b[0]), s[n - 1] = max(0, a[n].first - b[n - 1]);
    for (int i = 1; i < n; i++) p[i] = max(p[i - 1], a[i].first - b[i]);
    for (int i = n - 2; i >= 0; i--) s[i] = max(s[i + 1], a[i + 1].first - b[i]);
    x[a[0].second] = s[0], x[a[n].second] = p[n - 1];
    for (int i = 1; i < n; i++) x[a[i].second] = max(p[i - 1], s[i]);
    for (int i : x) cout << i << ' ';
}
