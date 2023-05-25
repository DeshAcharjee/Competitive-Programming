#include "horses.h"
#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
vector<int> x, y;
int n;

struct SegmentTree1 {
    vector<double> st, lz;
    vector<int> id;
    int sz;
    void init(const vector<double> &a) {
        sz = a.size();
        while (sz & sz - 1) ++sz;
        st.resize(sz << 1), lz.resize(sz << 1), id.resize(sz << 1);
        for (int i = 0; i < a.size(); i++) st[i + sz] = a[i] + log2(y[i]), id[i + sz] = i;
        for (int i = sz - 1; i; i--) pull(i);
    }
    void pull(int v) {
        if (st[v << 1] >= st[v << 1 | 1]) st[v] = st[v << 1], id[v] = id[v << 1];
        else st[v] = st[v << 1 | 1], id[v] = id[v << 1 | 1];
    }
    void push(int v) {
        st[v << 1] += lz[v];
        st[v << 1 | 1] += lz[v];
        lz[v << 1] += lz[v];
        lz[v << 1 | 1] += lz[v];
        lz[v] = 0;
    }
    void updx(int v, int l, int r, int ql, int qr, double x) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            st[v] += x, lz[v] += x;
            return;
        }
        if (lz[v] != 0) push(v);
        int m = l + r >> 1;
        updx(v << 1, l, m, ql, qr, x);
        updx(v << 1 | 1, m + 1, r, ql, qr, x);
        pull(v);
    }
    void updy(int v, int l, int r, int u, double y) {
        if (l == r) {
            st[v] += y;
            return;
        }
        if (lz[v] != 0) push(v);
        int m = l + r >> 1;
        if (u <= m) updy(v << 1, l, m, u, y);
        else updy(v << 1 | 1, m + 1, r, u, y);
        pull(v);
    }
    void updx(int l, int r, double x) {
        updx(1, 0, sz - 1, l, r, x);
    }
    void updy(int u, double y) {
        updy(1, 0, sz - 1, u, y);
    }
} st1;

struct SegmentTree2 {
    vector<int> st;
    int sz;
    void init(int n) {
        sz = n;
        st.resize(sz << 1);
    }
    void upd(int id, int x) {
        for (st[id += sz] = x; id >>= 1;) st[id] = 1LL * st[id << 1] * st[id << 1 | 1] % mod;
    }
    int qry(int l, int r) {
        int s = 1;
        for (l += sz, r += sz + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) s = 1LL * s * st[l++] % mod;
            if (r & 1) s = 1LL * s * st[--r] % mod;
        }
        return s;
    }
} st2;

int init(int N, int X[], int Y[]) {
    n = N, x.resize(n), y.resize(n);
    for (int i = 0; i < n; i++) x[i] = X[i], y[i] = Y[i];
    vector<double> p(n);
    p[0] = log2(x[0]);
    for (int i = 1; i < n; i++) p[i] = p[i - 1] + log2(x[i]);
    st1.init(p), st2.init(n);
    for (int i = 0; i < n; i++) st2.upd(i, x[i]);
    return 1LL * st2.qry(0, st1.id[1]) * y[st1.id[1]] % mod;
}

int updateX(int pos, int val) {
    st1.updx(pos, n - 1, log2(val) - log2(x[pos]));
    st2.upd(pos, val);
    x[pos] = val;
    return 1LL * st2.qry(0, st1.id[1]) * y[st1.id[1]] % mod;
}

int updateY(int pos, int val) {
    st1.updy(pos, log2(val) - log2(y[pos]));
    y[pos] = val;
    return 1LL * st2.qry(0, st1.id[1]) * y[st1.id[1]] % mod;
}
