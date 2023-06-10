#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int INF = 1e9;

typedef gp_hash_table<
    int, int, hash<int>, equal_to<int>, direct_mask_range_hashing<int>, linear_probe_fn<>,
    hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<true>, true>>
    gp;

struct node {
    gp mx;
    node* left;
    node* right;
    node() : left(NULL), right(NULL), mx(gp()), mx_(-INF) { };
    int mx_;
};

struct fenwick {
    vector<int> fenw;
    int n;
    void init(int n_) {
        fenw.resize(n = n_);
    }
    void add(int x) {
        for (; x < n; x |= x + 1) ++fenw[x];
    }
    void rem(int x) {
        for (; x < n; x |= x + 1) --fenw[x];
    }
    int qry(int x) {
        int s = 0;
        for (; x >= 0; x = (x & (x + 1)) - 1) s += fenw[x];
        return s;
    }
} BIT;

int n, x, y, cnt;
vector<int> a, cur;
vector<vector<bool>> bin;
node* root;

void build(node* &v, int lvl) {
    if (cur.empty()) return;
    if (v == NULL) v = new node();
    if (cur.size() == 1) return;
    vector<int> tmp = cur;
    cur.clear();
    for (int i = 0; i < tmp.size(); i++)
        if (i % 2 == 0)
            cur.push_back(tmp[i]);
    build(v->left, lvl + 1);
    cur.clear();
    for (int i = 0; i < tmp.size(); i++)
        if (i & 1) {
            bin[lvl][tmp[i]] = 1;
            cur.push_back(tmp[i]);
        }
    build(v->right, lvl + 1);
}

void add(int u) {
    node* v = root;
    for (int lvl = 0; v != NULL; ++lvl) {
        if (v->mx.find(a[u]) != v->mx.end()) {
            int p = v->mx[a[u]];
            if (p < u) {
                if (v->mx_ < p) {
                    if (v->mx_ != -INF) BIT.rem(v->mx_);
                    else ++cnt;
                    BIT.add(p);
                    v->mx_ = p;
                }
                v->mx[a[u]] = u;
            } else {
                if (v->mx_ < u) {
                    if (v->mx_ != -INF) BIT.rem(v->mx_);
                    else ++cnt;
                    BIT.add(u);
                    v->mx_ = u;
                }
            }
        } else v->mx[a[u]] = u;
        if (v->right && bin[lvl][u]) v = v->right;
        else v = v->left;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> x >> y;
    a.resize(n), cur.resize(n), BIT.init(n), bin = vector<vector<bool>> (18, vector<bool> (n));
    for (int i = 0; i < n; i++) cin >> a[i], --a[i];
    iota(cur.begin(), cur.end(), 0);
    build(root, 0);
    int q;
    cin >> q;
    vector<vector<pair<int, int>>> queries(n);
    vector<long long> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[--r].push_back({--l, i});
    }
    for (int r = 0; r < n; r++) {
        add(r);
        for (auto [l, id] : queries[r])
            ans[id] = x + 1LL * (x + y) * (cnt - BIT.qry(l - 1));
    }
    for (auto v : ans) cout << v << '\n';
}
