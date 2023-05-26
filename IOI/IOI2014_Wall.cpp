#include "wall.h"
#include <bits/stdc++.h>
using namespace std;
 
struct segtree {
    vector<int> st, t, o;
    int sz;
    segtree(int n) {
        sz = n;
        while (sz & sz - 1) ++sz;
        st.resize(sz << 1), o.resize(sz << 1, -1), t.resize(sz << 1);
    }
    void change(int v, int h, int op) {
        if (op == 4) {
            st[v] = h, o[v] = 4;
        } else if (o[v] == -1) {
            if (op == 2) {
                st[v] = 1e9, t[v] = h, o[v] = 1;
            } else {
                st[v] = h, t[v] = -1e9, o[v] = 0;
            }
        } else if (o[v] == 4) {
            if (op == 2) {
                st[v] = max(st[v], h);
            } else {
                st[v] = min(st[v], h);
            }
            t[v] = st[v];
        } else {
            if (op == 2) {
                t[v] = max(t[v], h);
                if (t[v] >= st[v]) {
                    st[v] = t[v];
                    o[v] = 4;
                }
            } else {
                st[v] = min(st[v], h);
                if (t[v] >= st[v]) {
                    t[v] = st[v];
                    o[v] = 4;
                }
            }
        }
    }
    void push(int v) {
        if ((v << 1) >= sz) {
            if (o[v] == 1) {
                st[v << 1] = min(st[v << 1], st[v]);
                st[v << 1] = max(st[v << 1], t[v]);
                st[v << 1 | 1] = min(st[v << 1 | 1], st[v]);
                st[v << 1 | 1] = max(st[v << 1 | 1], t[v]);
            } else if (o[v] == 0) {
                st[v << 1] = max(st[v << 1], t[v]);
                st[v << 1] = min(st[v << 1], st[v]);
                st[v << 1 | 1] = max(st[v << 1 | 1], t[v]);
                st[v << 1 | 1] = min(st[v << 1 | 1], st[v]);
            } else {
                st[v << 1] = st[v];
                st[v << 1 | 1] = st[v];
            }
        } else {
            if (o[v] == 1) {
                change(v << 1, st[v], 3);
                change(v << 1, t[v], 2);
                change(v << 1 | 1, st[v], 3);
                change(v << 1 | 1, t[v], 2);
            } else if (o[v] == 0) {
                change(v << 1, t[v], 2);
                change(v << 1, st[v], 3);
                change(v << 1 | 1, t[v], 2);
                change(v << 1 | 1, st[v], 3);
            } else {
                change(v << 1, st[v], 4);
                change(v << 1 | 1, st[v], 4);
            }
        }
        o[v] = -1;
    }
    void upd(int v, int l, int r, int ql, int qr, int op, int h) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            if (v < sz) change(v, h, op + 1);
            else {
                if (op == 2) st[v] = min(st[v], h);
                else st[v] = max(st[v], h);
            }
            return;
        }
        if (o[v] != -1) push(v);
        int m = l + r >> 1;
        upd(v << 1, l, m, ql, qr, op, h);
        upd(v << 1 | 1, m + 1, r, ql, qr, op, h);
    }
    void pushdown(int v) {
        if (v >= sz) return;
        if (o[v] != -1) push(v);
        pushdown(v << 1);
        pushdown(v << 1 | 1);
    }
    void upd(int l, int r, int op, int h) {
        upd(1, 0, sz - 1, l, r, op, h);
    }
    int get(int i) {
        return st[i + sz];
    }
};
 
void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalheight[]) {
    segtree st(n);
    for (int i = 0; i < k; i++) st.upd(left[i], right[i], op[i], height[i]);
    st.pushdown(1);
    for (int i = 0; i < n; i++) finalheight[i] = st.get(i);
}
