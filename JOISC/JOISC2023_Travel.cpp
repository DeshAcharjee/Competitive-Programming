#include <bits/stdc++.h>
using namespace std;

struct segtree {
    vector<int> tree;
    int sz, b, t;
    int merge(int a, int b) {
        return t ? min(a, b) : max(a, b);
    }
    segtree(vector<int> a, int tp) {
        t = tp;
        b = t ? 2e9 : -2e9;
        sz = a.size();
        while (sz & sz - 1) ++sz;
        tree.resize(sz << 1, b);
        for (int i = 0; i < a.size(); i++)
            tree[i + sz] = a[i];
        for (int i = sz - 1; i >= 1; i--)
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }
    int find_first(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql) return -1;
        if (l >= ql && r <= qr) {
            if (tree[v] > x) return -1;
            while (l < r) {
                int m = (l + r) >> 1;
                if (tree[v << 1] <= x) v <<= 1, r = m;
                else v = v << 1 | 1, l = m + 1;
            }
            return l;
        }
        int m = (l + r) >> 1;
        int left = find_first(v << 1, l, m, ql, qr, x);
        if (left != -1) return left;
        return find_first(v << 1 | 1, m + 1, r, ql, qr, x);
    }
    int find_last(int v, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql) return -1;
        if (l >= ql && r <= qr) {
            if (tree[v] <= x) return -1;
            while (l < r) {
                int m = (l + r) >> 1;
                if (tree[v << 1 | 1] > x) v = v << 1 | 1, l = m + 1;
                else v <<= 1, r = m;
            }
            return l;
        }
        int m = (l + r) >> 1;
        int right = find_last(v << 1 | 1, m + 1, r, ql, qr, x);
        if (right != -1) return right;
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
	int n;
    cin >> n;
    vector<int> diff(n), x(n), diff2(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 1; i < n; i++)
        diff[i] = 2 * x[i] - x[i - 1];
    for (int i = 0; i < n - 1; i++)
        diff2[i] = 2 * x[i] - x[i + 1];
    diff[0] = 2e9, diff2[n - 1] = -2e9;
    segtree tree1(diff, 0), tree2(diff2, 1);
    int q;
    cin >> q;
    while (q--) {
        int p;
        cin >> p;
        auto it = lower_bound(x.begin(), x.end(), p);
        int k;
        if (it != x.end()) {
            k = it - x.begin();
            if (it != x.begin()) {
                it--;
                if (p - *it <= x[k] - p)
                    k = it - x.begin();
            }
        } else k = n - 1;
        int l = k, r = k, ans = abs(p - x[k]), cur = k;
        while (l != 0 || r != n - 1) {
            if (r == n - 1) {
                ans += x[cur] - x[0];
                break;
            }
            if (l == 0) {
                ans += x[n - 1] - x[cur];
                break;
            }
            if (cur ^ r) {
                int left = tree1.find_last(0, l, x[r + 1]);
                ans += x[cur] - (x[left] << 1) + x[r + 1];
                l = left, cur = ++r;
            } else {
                int right = tree2.find_first(r, n - 1, x[l - 1]);
                ans += (x[right] << 1) - x[cur] - x[l - 1];
                r = right, cur = --l;
            }
        }
        cout << ans << '\n';
    }
}
