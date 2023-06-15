#include <bits/stdc++.h>
using namespace std;

struct fenwick {
    vector<long long> fenw;
    int n;
    fenwick(int n_) : n(n_) {
        fenw.resize(n);
    }
    void upd(int i, int d) {
        for (; i < n; i |= i + 1) fenw[i] += d;
    }
    long long qry(int i) {
        long long s = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) s += fenw[i];
        return s;
    }
    void upd(int l, int r, int d) {
        upd(l, d);
        upd(r + 1, -d);
    }
    void reset() {
        for (int i = 0; i < n; i++) fenw[i] = 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> p(n), ans(n, -1), l(n), r(n);
    vector<vector<int>> v(n);
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        --x;
        v[x].push_back(i);
    }
    for (int i = 0; i < n; i++) cin >> p[i];
    fenwick fen(m);
    int k;
    cin >> k;
    vector<tuple<int, int, int>> queries(k);
    vector<vector<int>> q(k);
    for (auto &[l_, r_, w] : queries) cin >> l_ >> r_ >> w, --l_, --r_;
    for (int i = 0; i < n; i++) q[(k - 1) >> 1].push_back(i), r[i] = k - 1;
    for (int itr = 0; itr < 19; itr++) {
        for (int i = 0; i < k; i++) {
            auto [l_, r_, w] = queries[i];
            if (l_ <= r_) fen.upd(l_, r_, w);
            else fen.upd(l_, m - 1, w), fen.upd(0, r_, w);
            for (int j : q[i]) {
                long long sum = 0;
                for (int x : v[j]) {
                    if (sum < p[j]) sum += fen.qry(x);
                    else break;
                }
                if (sum >= p[j]) ans[j] = i, r[j] = i - 1;
                else l[j] = i + 1;
            }
            for (int j : q[i]) {
                int mid = l[j] + r[j] >> 1;
                if (mid != i && l[j] <= r[j]) q[mid].push_back(j);
            }
            q[i].clear();
        }
        fen.reset();
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1) cout << "NIE\n";
        else cout << ans[i] + 1 << '\n';
    }
}
