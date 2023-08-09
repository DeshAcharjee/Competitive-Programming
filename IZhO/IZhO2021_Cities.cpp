#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> st;
    int sz;
    SegmentTree(const vector<int> &a) : sz(a.size()) {
        while (sz & sz - 1) ++sz;
        st.resize(sz << 1, 2e9);
        for (int i = 0; i < a.size(); i++) st[i + sz] = a[i];
        for (int i = sz - 1; i; i--) st[i] = min(st[i << 1], st[i << 1 | 1]);
    }
    int find_first(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql) return -1;
        if (l >= ql && r <= qr) {
            if (st[v] >= x) return -1;
            while (l < r) {
                int m = l + r >> 1;
                if (st[v << 1] < x) v <<= 1, r = m;
                else v = v << 1 | 1, l = m + 1;
            }
            return l;
        }
        int m = l + r >> 1;
        int id = find_first(v << 1, l, m, ql, qr, x);
        if (id != -1) return id;
        return find_first(v << 1 | 1, m + 1, r, ql, qr, x);
    }
    int find_last(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql) return -1;
        if (l >= ql && r <= qr) {
            if (st[v] >= x) return -1;
            while (l < r) {
                int m = l + r >> 1;
                if (st[v << 1 | 1] < x) v = v << 1 | 1, l = m + 1;
                else v <<= 1, r = m;
            }
            return l;
        }
        int m = l + r >> 1;
        int id = find_last(v << 1 | 1, m + 1, r, ql, qr, x);
        if (id != -1) return id;
        return find_last(v << 1, l, m, ql, qr, x);
    }
    int find_first(int l, int r, int x) {
        return find_first(1, 0, sz - 1, l, r, x);
    }
    int find_last(int l, int r, int x) {
        return find_last(1, 0, sz - 1, l, r, x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, s, t;
    cin >> n >> s >> t;
    --s, --t;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    SegmentTree st(a);
    vector<int> pf(n), sf(n);
    for (int i = 0; i < n; i++) pf[i] = st.find_last(0, i, a[i]), sf[i] = st.find_first(i, n - 1, a[i]);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, s});
    long long ans = 1e18;
    while (pq.size()) {
        auto [x, y] = pq.top();
        pq.pop();
        if (x >= ans) break;
        ans = min(ans, x + (long long) abs(t - y) * a[y]);
        if (pf[y] != -1) pq.push({x + (long long) (y - pf[y]) * a[y], pf[y]});
        if (sf[y] != -1) pq.push({x + (long long) (sf[y] - y) * a[y], sf[y]});
    }
    cout << ans << '\n';
    return 0;
}
