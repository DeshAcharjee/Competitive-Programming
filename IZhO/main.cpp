#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, x, ans = 0;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> p1, p2;
    for (int i = 0; i < n; i++) {
        cin >> x;
        p1.push(x);
    }
    for (int i = 0; i < n; i++) {
        cin >> x;
        p2.push(x);
    }
    while (p1.size()) {
        int x = p1.top(), y = p2.top();
        p1.pop(), p2.pop();
        if (x > y) {
            p1.push(y);
            p2.push(x);
            ++ans;
        }
    }
    cout << ans << '\n';
}
