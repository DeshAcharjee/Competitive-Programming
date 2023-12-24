#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t, c;
    cin >> t >> c;
    vector<bool> target(2 * c + 1);
    for (int i = 0; i < t; i++) {
        int x;
        cin >> x;
        target[x + c] = 1;
    }
    string s;
    cin >> s;
    vector<int> cnt(2 * c + 1), hit(5);
    vector<vector<bool>> f(5, vector<bool> (2 * c + 1));
    int cur = c, p = 0;
    for (int i = 0; i < c; i++) {
        if (s[i] == 'L') {
            --cur;
        } else if (s[i] == 'R') {
            ++cur;
        } else if (target[cur] && !cnt[cur]++) {
            ++p;
        }
    }
    int ans = p;
    for (int i = c - 1; i >= 0; i--) {
        if (s[i] == 'L') {
            ++cur;
            ans = max({ans, p + hit[3] + (target[cur] && !cnt[cur] && !f[3][cur]), p + hit[4]});
        } else if (s[i] == 'R') {
            --cur;
            ans = max({ans, p + hit[1] + (target[cur] && !cnt[cur] && !f[1][cur]), p + hit[0]});
        } else {
            ans = max({ans, p + hit[1] - (cnt[cur] == 1 && !f[1][cur]), p + hit[3] - (cnt[cur] == 1 && !f[3][cur])});
            if (target[cur] && !--cnt[cur]) {
                --p;
                for (int dx = -2; dx <= 2; dx++) {
                    if (f[dx + 2][cur]) {
                        ++hit[dx + 2];
                    }
                }
            }
            for (int dx = -2; dx <= 2; dx++) {
                if (cur + dx >= 0 && cur + dx <= 2 * c && target[cur + dx] && !f[dx + 2][cur + dx]) {
                    f[dx + 2][cur + dx] = 1;
                    if (!cnt[cur + dx]) {
                        ++hit[dx + 2];
                    }
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}