#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(k), b(k);
    for (int &x : a) {
        cin >> x;
        --x;
    }
    for (int &x : b) {
        cin >> x;
        --x;
    }
    int ans = 0;
    for (int it = 0; it < 2; it++) {
        vector<int> posA(n, -1), posB(n, -1), cntrev(k + 1), cntfront(k + 1);
        for (int i = 0; i < k; i++) {
            posA[a[i]] = i;
        }
        for (int i = 0; i < k; i++) {
            posB[b[i]] = i;
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (posA[i] == -1 && posB[i] == -1) {
                ++cnt;
                continue;
            }
            if (posA[i] == -1 || posB[i] == -1) continue;
            if (posA[i] < posB[i]) {
                ++cntfront[posB[i] - posA[i]];
                ++cntrev[posA[i] - posB[i] + k];
            } else {
                ++cntrev[posA[i] - posB[i]];
                ++cntfront[posB[i] - posA[i] + k];
            }
        }
        ans = max(ans, cnt + max(*max_element(cntrev.begin(), cntrev.end()), *max_element(cntfront.begin(), cntfront.end())));
        reverse(a.begin(), a.end());
    }
    cout << ans << '\n';
    return 0;
}
