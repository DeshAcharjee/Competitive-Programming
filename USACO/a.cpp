#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> cows(n);
    for (auto &[w, a] : cows) {
        cin >> w >> a;
    }
    sort(cows.begin(), cows.end());
    map<int, int> towers;
    towers[-k] = m;
    long long ans = 0;
    for (auto [w, a] : cows) {
        int cur = 0;
        while (a) {
            auto it = towers.upper_bound(w - k);
            if (it == towers.begin()) break;
            --it;
            if (it->second > a) {
                cur += a;
                towers[it->first] -= a;
                a = 0;
            } else {
                cur += it->second;
                a -= it->second;
                towers.erase(it);
            }
        }
        ans += cur;
        if (cur) {
            towers[w] = cur;
        }
    }
    cout << ans << '\n';
    return 0;
}