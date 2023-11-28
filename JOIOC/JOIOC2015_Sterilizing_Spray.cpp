#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    vector<long long> T;
    int n;
    SegmentTree(const vector<int> &v) : n(v.size()) {
        while (n & n - 1) ++n;
        T.resize(n << 1);
        for (int i = 0; i < v.size(); i++) {
            T[i + n] = v[i];
        }
        for (int i = n - 1; i > 0; i--) {
            T[i] = T[i << 1] + T[i << 1 | 1];
        }
    }
    void upd0(int v, int l, int r, int u, int x) {
        if (l == r) {
            T[v] = x;
            return;
        }
        int m = l + r >> 1;
        if (u <= m) upd0(v << 1, l, m, u, x);
        else upd0(v << 1 | 1, m + 1, r, u, x);
        T[v] = T[v << 1] + T[v << 1 | 1];
    }
    void upd1(int v, int l, int r, int ql, int qr, const int &x) {
        if (l > qr || r < ql || !T[v]) return;
        if (l == r) {
            T[v] /= x;
            return;
        }
        int m = l + r >> 1;
        upd1(v << 1, l, m, ql, qr, x);
        upd1(v << 1 | 1, m + 1, r, ql, qr, x);
        T[v] = T[v << 1] + T[v << 1 | 1];
    }
    long long qry(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return T[v];
        int m = l + r >> 1;
        return qry(v << 1, l, m, ql, qr) + qry(v << 1 | 1, m + 1, r, ql, qr);
    }
    void upd0(int u, int x) {
        upd0(1, 0, n - 1, u, x);
    }
    void upd1(int l, int r, const int &x) {
        upd1(1, 0, n - 1, l, r, x);
    }
    long long qry(int l, int r) {
        return qry(1, 0, n - 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q, k;
    cin >> n >> q >> k;
    vector<int> v(n);
    for (int &x : v) {
        cin >> x;
    }
    SegmentTree st(v);
    while (q--) {
        int s, t, u;
        cin >> s >> t >> u;
        if (s == 1) {
            st.upd0(--t, u);
        } else if (s == 2) {
            if (k > 1) st.upd1(--t, --u, k);
        } else {
            cout << st.qry(--t, --u) << '\n';
        }
    }
    return 0;
}
