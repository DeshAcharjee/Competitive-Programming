#include "shoes.h"
#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> tr, lz;
    int sz;
    SegmentTree(int n) {
        sz = n;
        while (sz & sz - 1) ++sz;
        tr.resize(sz << 1), lz.resize(sz << 1);
    }
    void push(int v, int l, int r) {
        int m = l + r >> 1;
        tr[v << 1] += lz[v] * (m - l + 1);
        lz[v << 1] += lz[v];
        tr[v << 1 | 1] += lz[v] * (r - m);
        lz[v << 1 | 1] += lz[v];
        lz[v] = 0;
    }
    void upd(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            tr[v] += r - l + 1;
            lz[v]++;
            return;
        }
        if (lz[v]) push(v, l, r);
        int m = l + r >> 1;
        upd(v << 1, l, m, ql, qr);
        upd(v << 1 | 1, m + 1, r, ql, qr);
        tr[v] = tr[v << 1] + tr[v << 1 | 1];
    }
    int query(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tr[v];
        if (lz[v]) push(v, l, r);
        int m = l + r >> 1;
        return query(v << 1, l, m, ql, qr) + query(v << 1 | 1, m + 1, r, ql, qr);
    }
    int query(int i) {
        return query(1, 0, sz - 1, i, i);
    }
    void upd(int l, int r) {
        if (l > r) return;
        upd(1, 0, sz - 1, l, r);
    }
};

long long count_swaps(vector<int> s) {
    map<int, set<int>> mp;
    int n = s.size();
    SegmentTree st(n);
    for (int i = 0; i < n; i++) {
        mp[s[i]].insert(i);
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (mp[s[i]].find(i) == mp[s[i]].end()) continue;
        auto it = mp[-s[i]].begin();
        if (s[i] < 0) {
            ans += (*it + st.query(*it)) - (i + st.query(i)) - 1, st.upd(i + 1, *it - 1);
        } else {
            ans += (*it + st.query(*it)) - (i + st.query(i)), st.upd(i, *it - 1);
        }
        mp[s[i]].erase(i), mp[-s[i]].erase(it);
    }
    return ans;
}
