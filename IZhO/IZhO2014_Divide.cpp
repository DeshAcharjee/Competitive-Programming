#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

struct segtree {
    vector<long long> st;
    int sz;
    segtree(vector<long long> a) {
        sz = a.size();
        while (sz & sz - 1) ++sz;
        st.resize(sz << 1, INF);
        for (int i = 0; i < a.size(); i++) st[i + sz] = a[i];
        for (int i = sz - 1; i; --i) pull(i);
    }
    void pull(int v) {
        st[v] = min(st[v << 1], st[v << 1 | 1]);
    }
    int findfirst(int v, int l, int r, int ql, int qr, long long x) {
        if (l > qr || r < ql) return -1;
        if (l >= ql && r <= qr) {
            if (st[v] > x) return -1;
            while (l < r) {
                int m = l + r >> 1;
                if (st[v << 1] <= x) v <<= 1, r = m;
                else v <<= 1, v |= 1, l = m + 1;
            }
            return l;
        }
        int m = l + r >> 1;
        int s = findfirst(v << 1, l, m, ql, qr, x);
        if (s != -1) return s;
        return findfirst(v << 1 | 1, m + 1, r, ql, qr, x);
    }
    int findfirst(int l, int r, long long x) {
        return findfirst(1, 0, sz - 1, l, r, x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> x(n), g(n), d(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> g[i] >> d[i];
    vector<long long> pre1(n + 1), pre2(n + 1), f(n + 1);
    for (int i = 0; i < n; i++) pre1[i + 1] = pre1[i] + g[i], pre2[i + 1] = pre2[i] + d[i];
    f[0] = INF;
    for (int i = 1; i <= n; i++) f[i] = pre2[i - 1] - x[i - 1];
    segtree st(f);
    long long ans = -INF;
    for (int i = 1; i <= n; i++) {
        int k = st.findfirst(0, i, pre2[i] - x[i - 1]);
        if (k == -1) continue;
        ans = max(ans, pre1[i] - pre1[k - 1]);
    }
    cout << ans << '\n';
}
