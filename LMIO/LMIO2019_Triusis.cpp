#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> lis;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x <= i * m) {
            auto it = upper_bound(lis.begin(), lis.end(), i * m - x);
            if (it == lis.end()) lis.push_back(i * m - x);
            else *it = i * m - x;
        }
    }
    cout << n - lis.size() << '\n';
    return 0;
}
