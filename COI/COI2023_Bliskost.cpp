#include <bits/stdc++.h>
using namespace std;

struct segtree {
    vector<int> st;
    int n;
    segtree(int n_) : n(n_) { st.resize(n << 1); }
    void upd(int u, int x) { for (st[u += n] = x; u >>= 1;) st[u] = st[u << 1] + st[u << 1 | 1]; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        a[i] = c - 'a';
    }
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        b[i] = c - 'a';
    }
    segtree st(n - 1);
    int k = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (i % 2 == (n - 2) % 2) k += b[i], st.upd(i, -a[i]);
        else k -= b[i], st.upd(i, a[i]);
    }
    if (n == 1) cout << (a[n - 1] == b[n - 1] ? "da" : "ne") << '\n';
    else cout << ((((st.st[1] + a[n - 1] + k) % 26) + 26) % 26 == b[n - 1] ? "da" : "ne") << '\n';
    while (q--) {
        int id;
        char c;
        cin >> id >> c;
        a[--id] = c - 'a';
        if (id != n - 1) st.upd(id, id % 2 == (n - 2) % 2 ? -a[id] : a[id]);
        if (n == 1) cout << (a[n - 1] == b[n - 1] ? "da" : "ne") << '\n';
        else cout << ((((st.st[1] + a[n - 1] + k) % 26) + 26) % 26 == b[n - 1] ? "da" : "ne") << '\n';
    }
}
