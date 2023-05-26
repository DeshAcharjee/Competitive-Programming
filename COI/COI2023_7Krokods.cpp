#include <bits/stdc++.h>
using namespace std;

vector<char> cards = {'d', 'k', 'o', 'r'};
int m;
vector<string> combs;
map<string, bool> mem;

void recurse(string z, int k) {
    sort(z.begin(), z.end());
    if (mem.find(z) != mem.end()) return;
    mem[z] = 1;
    if (k == m) {
        combs.push_back(z);
        return;
    }
    for (char card : cards) {
        z.push_back(card);
        recurse(z, k + 1);
        z.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string y;
    recurse(y, 0);
    int n;
    cin >> n >> m;
    string r;
    cin >> r;
    int ans2 = 0;
    for (int k = 0; k < combs.size(); k++) {
        string s = r + combs[k];
        map<int, int> mp;
        for (char f : cards) mp[f - 'a'] = 0;
        for (int i = 0; i < s.size(); i++) ++mp[s[i] - 'a'];
        int ans = 0, w = 1e9;
        for (auto [x, y] : mp) ans += y * y;
        for (auto [x, y] : mp) {
            if (('a' + x) == 'k' || ('a' + x) == 'o') w = min(y / 2, w);
            else w = min(y, w);
        }
        ans2 = max(ans + 7 * w, ans2);
    }
    cout << ans2 << '\n';
}
