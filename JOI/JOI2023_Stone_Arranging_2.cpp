#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> r;
    for (int i = 0; i < n; i++) cin >> a[i], r[a[i]] = i;
    for (int i = 0; i < n; i = r[a[i]] + 1)
        for (int j = i; j <= r[a[i]]; j++) cout << a[i] << '\n';
    return 0;
}
