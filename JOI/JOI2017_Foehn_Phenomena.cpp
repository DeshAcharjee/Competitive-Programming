#include <bits/stdc++.h>
using namespace std;

template<typename T>
    struct fenwick {
        vector<T> fenw;
        int n;
        fenwick(int n_) : n(n_) {
            fenw.resize(n);
        }
        void upd(int id, int x) {
            while (id < n) {
                fenw[id] += x;
                id |= id + 1;
            }
        }
        T qry(int id) {
            T s = 0;
            while (id >= 0) {
                s += fenw[id];
                id = (id & (id + 1)) - 1;
            }
            return s;
        }
        void upd(int l, int r, int x) {
            upd(l, x);
            upd(r + 1, -x);
        }
    };

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q, s, t, p = 0;
    cin >> n >> q >> s >> t;
    fenwick<long long> bit(n + 1);
    long long ans = 0, x;
    for (int i = 0; i <= n; i++) {
        int x;
        cin >> x;
        bit.upd(i, i, x);
        ans += (x > p ? -1LL * s  * (x - p): 1LL * t * (p - x));
        p = x;
    }
    while (q--) {
        int l, r;
        cin >> l >> r >> x;
        long long a1 = bit.qry(l), a2 = (l == r ? a1 : bit.qry(r));
        bit.upd(l, r, x);
        long long p1 = bit.qry(l - 1), p2 = (r == n ? -1 : bit.qry(r + 1));
        if (p1 < a1 && p1 >= a1 + x) ans += (a1 - p1) * s + t * (p1 - a1 - x);
        else if (p1 >= a1 + x) ans -= x * t;
        if (p1 >= a1 && p1 < a1 + x) ans -= (a1 + x - p1) * s + (p1 - a1) * t;
        else if (p1 < a1 + x) ans -= x * s;
        if (r != n) {
            if (a2 < p2 && a2 + x >= p2) ans += (p2 - a2) * s + t * (a2 + x - p2);
            else if (a2 + x >= p2) ans += x * t;
            if (a2 >= p2 && a2 + x < p2) ans -= (a2 - p2) * t + (p2 - a2 - x) * s;
            else if (a2 + x < p2) ans += x * s;
        }
        cout << ans << '\n';
    }
}
