#include <bits/stdc++.h>
using namespace std;

template <typename T>
    struct fenwick {
        vector<T> fen;
        int n;
        fenwick(int n_) : n(n_) {
            fen.resize(n);
        }
        void upd(int x, T d) {
            while (x < n) {
                fen[x] += d;
                x |= x + 1;
            }
        }
        T qry(int x) {
            T s = 0;
            while (x >= 0) {
                s += fen[x];
                x = (x & (x + 1)) - 1;
            }
            return s;
        }
        void upd(int l, int r, T d) {
            upd(l, d);
            upd(r + 1, -d);
        }
    };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    fenwick<long long> fen(n);
    for (int i = 0; i < n; i++) cin >> a[i], fen.upd(i, i, a[i]);
    long long ans = 0;
    for (int i = 1, j = n - 1; i <= j; i++) {
        long long a = fen.qry(i - 1), b = fen.qry(i);
        while (a >= b) {
            while (j && fen.qry(j - 1) > fen.qry(j)) --j;
            if (j <= i) {
                if (a == b) ans++;
                break;
            }
            long long w = fen.qry(j), w2 = fen.qry(j - 1);
            if (w - w2 >= a - b) {
                fen.upd(i, j - 1, a - b + 1);
                ans += a - b + 1;
                break;
            }
            fen.upd(i, j - 1, w - w2 + 1);
            ans += w - w2 + 1, b += w - w2 + 1;
        }
    }
    cout << ans << '\n';
}
