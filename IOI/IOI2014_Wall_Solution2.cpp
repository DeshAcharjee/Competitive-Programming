#include <bits/stdc++.h>
 
using namespace std;
 
const int INF = 2e9;
 
struct node {
    int mn1;
    int mn2;
    int mx1;
    int mx2;
    int mncnt;
    int mxcnt;
    int sum;
    int lz;
    node() : mn1(INF), mn2(INF), mx1(-INF), mx2(-INF), mncnt(0), mxcnt(0), sum(0), lz(0) { };
};
 
struct SegmentTreeBeats {
    vector<node> st;
    int sz;
    void build(int v, int l, int r, vector<int> &a) {
        if (l == r) {
            st[v].mn1 = a[l];
            st[v].mx1 = a[l];
            st[v].mncnt = st[v].mxcnt = 1;
            st[v].sum = a[l];
            return;
        }
        int m = l + r >> 1;
        build(v << 1, l, m, a);
        build(v << 1 | 1, m + 1, r, a);
        pull(v);
    }
    void applyleaf(int v, int x) {
        st[v].mn1 = x;
        st[v].mx1 = x;
        st[v].mncnt = st[v].mxcnt = 1;
        st[v].sum = x;
    }
    SegmentTreeBeats(const vector<int> &a) : sz(a.size()) {
        while (sz & sz - 1) ++sz;
        st.resize(sz << 1);
        for (int i = 0; i < a.size(); i++) applyleaf(i + sz, a[i]);
        for (int i = sz - 1; i > 0; i--) pull(i);
    }
    SegmentTreeBeats(int n) : sz(n) {
        while (sz & sz - 1) ++sz;
        st.resize(sz << 1);
        for (int i = 0; i < n; i++) {
            applyleaf(i + sz, 0);
        }
        for (int i = sz - 1; i > 0; i--) {
            pull(i);
        }
    }
    void apply1(int v, int x, int l, int r) {
        if (x == 0) return;
        st[v].mx1 += x;
        if (st[v].mx2 != -INF) st[v].mx2 += x;
        st[v].mn1 += x;
        if (st[v].mn2 != INF) st[v].mn2 += x;
        st[v].sum += (r - l + 1) * x;
        st[v].lz += x;
    }
    void apply2(int v, int x, bool f) {
        if (st[v].mn1 >= x) return;
        st[v].sum = st[v].sum - st[v].mncnt * st[v].mn1 + st[v].mncnt * x;
        if (f) {
            st[v].mn1 = st[v].mx1 = x;
        } else {
            st[v].mn1 = x;
            if (x >= st[v].mx1) st[v].mx1 = x;
            else if (x > st[v].mx2) st[v].mx2 = x;
        }
    }
    void apply3(int v, int x, bool f) {
        if (st[v].mx1 <= x) return;
        st[v].sum = st[v].sum - st[v].mxcnt * st[v].mx1 + st[v].mxcnt * x;
        if (f) {
            st[v].mx1 = st[v].mn1 = x;
        } else {
            st[v].mx1 = x;
            if (x <= st[v].mn1) st[v].mn1 = x;
            else if (x < st[v].mn2) st[v].mn2 = x;
        }
    }
    void push(int v, int l, int r) {
        int m = l + r >> 1;
        apply1(v << 1, st[v].lz, l, m);
        apply1(v << 1 | 1, st[v].lz, m + 1, r);
        st[v].lz = 0;
        apply2(v << 1, st[v].mn1, l == m);
        apply2(v << 1 | 1, st[v].mn1, m + 1 == r);
        apply3(v << 1, st[v].mx1, l == m);
        apply3(v << 1 | 1, st[v].mx1, m + 1 == r);
    }
    void pull(int v) {
        st[v].sum = st[v << 1].sum + st[v << 1 | 1].sum;
        if (st[v << 1].mn1 == st[v << 1 | 1].mn1) {
            st[v].mn1 = st[v << 1].mn1;
            st[v].mncnt = st[v << 1].mncnt + st[v << 1 | 1].mncnt;
            st[v].mn2 = min(st[v << 1].mn2, st[v << 1 | 1].mn2);
        } else if (st[v << 1].mn1 > st[v << 1 | 1].mn1) {
            st[v].mn1 = st[v << 1 | 1].mn1;
            st[v].mncnt = st[v << 1 | 1].mncnt;
            st[v].mn2 = min(st[v << 1].mn1, st[v << 1 | 1].mn2);
        } else {
            st[v].mn1 = st[v << 1].mn1;
            st[v].mncnt = st[v << 1].mncnt;
            st[v].mn2 = min(st[v << 1].mn2, st[v << 1 | 1].mn1);
        }
        if (st[v << 1].mx1 == st[v << 1 | 1].mx1) {
            st[v].mx1 = st[v << 1].mx1;
            st[v].mxcnt = st[v << 1].mxcnt + st[v << 1 | 1].mxcnt;
            st[v].mx2 = max(st[v << 1].mx2, st[v << 1 | 1].mx2);
        } else if (st[v << 1].mx1 < st[v << 1 | 1].mx1) {
            st[v].mx1 = st[v << 1 | 1].mx1;
            st[v].mxcnt = st[v << 1 | 1].mxcnt;
            st[v].mx2 = max(st[v << 1].mx1, st[v << 1 | 1].mx2);
        } else {
            st[v].mx1 = st[v << 1].mx1;
            st[v].mxcnt = st[v << 1].mxcnt;
            st[v].mx2 = max(st[v << 1].mx2, st[v << 1 | 1].mx1);
        }
    }
    void upd1(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            apply1(v, x, l, r);
            return;
        }
        push(v, l, r);
        int m = l + r >> 1;
        upd1(v << 1, l, m, ql, qr, x);
        upd1(v << 1 | 1, m + 1, r, ql, qr, x);
        pull(v);
    }
    void upd2(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql || st[v].mn1 >= x) return;
        if (l >= ql && r <= qr && st[v].mn2 > x) {
            apply2(v, x, l == r);
            return;
        }
        push(v, l, r);
        int m = l + r >> 1;
        upd2(v << 1, l, m, ql, qr, x);
        upd2(v << 1 | 1, m + 1, r, ql, qr, x);
        pull(v);
    }
    void upd3(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql || st[v].mx1 <= x) return;
        if (l >= ql && r <= qr && st[v].mx2 < x) {
            apply3(v, x, l == r);
            return;
        }
        push(v, l, r);
        int m = l + r >> 1;
        upd3(v << 1, l, m, ql, qr, x);
        upd3(v << 1 | 1, m + 1, r, ql, qr, x);
        pull(v);
    }
    void pushdown(int v, int l, int r) {
        if (l == r) return;
        push(v, l, r);
        int m = l + r >> 1;
        pushdown(v << 1, l, m);
        pushdown(v << 1 | 1, m + 1, r);
    }
    int qry(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return st[v].sum;
        push(v, l, r);
        int m = l + r >> 1;
        return qry(v << 1, l, m, ql, qr) + qry(v << 1 | 1, m + 1, r, ql, qr);
    }
    void pushdown() {
        pushdown(1, 0, sz - 1);
    }
    void upd1(int l, int r, int x) {
        upd1(1, 0, sz - 1, l, r, x);
    }
    void upd2(int l, int r, int x) {
        upd2(1, 0, sz - 1, l, r, x);
    }
    void upd3(int l, int r, int x) {
        upd3(1, 0, sz - 1, l, r, x);
    }
    int qry(int l, int r) {
        return qry(1, 0, sz - 1, l, r);
    }
    int get(int id) {
        return st[id + sz].mx1;
    }
};
 
void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalheight[]) {
    SegmentTreeBeats st(n);
    for (int i = 0; i < k; i++) {
        if (op[i] == 1) {
            st.upd2(left[i], right[i], height[i]);
        } else {
            st.upd3(left[i], right[i], height[i]);
        }
    }
    st.pushdown();
    for (int i = 0; i < n; i++) {
        finalheight[i] = st.get(i);
    }
}
