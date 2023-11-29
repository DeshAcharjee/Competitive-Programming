#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for (auto &x : s) {
        cin >> x;
    }
    vector<int> I(w);
    long long ans = 0;
    for (int i = h - 1; i >= 0; i--) {
        for (int j = w - 1, O = 0; j >= 0; j--) {
            if (s[i][j] == 'O') ++O;
            else if (s[i][j] == 'I') ++I[j];
            else ans += O * I[j];
        }
    }
    cout << ans << '\n';
    return 0;
}
