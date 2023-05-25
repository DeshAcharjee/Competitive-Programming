#include <bits/stdc++.h>
using namespace std;

struct node {
    int mx, h, d, delta;
    node *left, *right;
    node() : h(0), d(0), mx(0), delta(0), left(NULL), right(NULL) { };
    void pull() {
        mx = max(left->mx, right->mx);
    }
    void push(int l, int r) {
        int m = l + r >> 1;
        if (left == NULL) left = new node();
        if (right == NULL) right = new node();
        if (h != -1) {
            left->h = h;
            left->d = d;
            right->h = h + (m - l + 1) * d;
            right->d = d;
            if (d < 0) {
                left->mx = left->h;
                right->mx = right->h;
            } else {
                left->mx = h + (m - l) * d;
                right->mx = h + (r - l) * d;
            }
            h = -1;
            delta = 0;
        }
        if (delta) {
            left->mx += delta;
            if (left->h != -1) left->h += delta;
            else left->delta += delta;
            right->mx += delta;
            if (right->h != -1) right->h += delta;
            else right->delta += delta;
            delta = 0;
        }
    }
};

struct SegmentTree {
    node *root;
    int n;
    SegmentTree(int n_) : root(new node()), n(n_) { };
    void upd(node* &v, int l, int r, int ql, int qr, int h, int d) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            v->delta = 0;
            v->h = h + (l - ql + 1) * d, v->d = d;
            v->mx = d < 0 ? v->h : v->h + (r - l) * d;
            return;
        }
        v->push(l, r);
        int m = l + r >> 1;
        upd(v->left, l, m, ql, qr, h, d);
        upd(v->right, m + 1, r, ql, qr, h, d);
        v->pull();
    }
    void upd2(node* &v, int l, int r, int ql, int qr, int delta) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            v->mx += delta;
            if (v->h != -1) v->h += delta;
            else v->delta += delta;
            return;
        }
        v->push(l, r);
        int m = l + r >> 1;
        upd2(v->left, l, m, ql, qr, delta);
        upd2(v->right, m + 1, r, ql, qr, delta);
        v->pull();
    }
    int find_first(node* &v, int l, int r, int h) {
        if (l == r) return l;
        int m = l + r >> 1;
        v->push(l, r);
        if (v->left->mx > h) return find_first(v->left, l, m, h);
        return find_first(v->right, m + 1, r, h);
    }
    int qry(node* &v, int l, int r, int u) {
        if (l == r) return v->mx;
        v->push(l, r);
        int m = l + r >> 1;
        if (u <= m) return qry(v->left, l, m, u);
        return qry(v->right, m + 1, r, u);
    }
    int qry(int u) {
        return qry(root, 0, n, u);
    }
    int find_first(int h) {
        return find_first(root, 0, n, h);
    }
    void upd(int l, int r, int d) {
        upd(root, 0, n, l, r, qry(l - 1), d);
    }
    void upd2(int l, int r, int delta) {
        upd2(root, 0, n, l, r, delta);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    SegmentTree SegmentTree(n);
    while (1) {
        char c;
        cin >> c;
        if (c == 'E') break;
        if (c == 'Q') {
            int h;
            cin >> h;
            cout << (SegmentTree.root->mx <= h ? n : SegmentTree.find_first(h) - 1) << '\n';
        } else {
            int l, r, d;
            cin >> l >> r >> d;
            int x = SegmentTree.qry(r);
            SegmentTree.upd(l, r, d);
            if (r ^ n) SegmentTree.upd2(r + 1, n, SegmentTree.qry(r) - x);
        }
    }
}
