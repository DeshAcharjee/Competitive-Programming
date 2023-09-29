#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

template<typename T>
    struct SegmentTree {
        vector<T> st;
        int n;
        SegmentTree(int n_) : n(n_) {
            st.resize(n << 1, INF);
        }
        void update(int i, T x) {
            i += n;
            st[i] = min(st[i], x);
            while (i >>= 1) st[i] = min(st[i << 1], st[i << 1 | 1]);
        }
        T query(int l, int r) {
            T mn = INF;
            for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) mn = min(mn, st[l++]);
                if (r & 1) mn = min(mn, st[--r]);
            }
            return mn;
        }
    };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m, n;
    cin >> m >> n;
    vector<tuple<int, int, int, int>> q(m);
    vector<int> cmp;
    for (auto &[a, b, c, d] : q) {
        cin >> a >> b >> c >> d;
        --a, --b, --c;
        cmp.push_back(a);
        cmp.push_back(b);
        cmp.push_back(c);
    }
    sort(cmp.begin(), cmp.end());
    if (cmp[0] || cmp.back() != n - 1) {
        cout << "-1\n";
        return 0;
    }
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    auto Compress = [&](int &x) -> void {
        x = lower_bound(cmp.begin(), cmp.end(), x) - cmp.begin();
    };
    n = cmp.size();
    SegmentTree<long long> l(n), r(n);
    long long ans = INF;
    for (auto &[a, b, c, d] : q) {
        Compress(a), Compress(b), Compress(c);
        if (!a && b == n - 1) {
            ans = min(ans, (long long) d);
        } else if (!a) {
            long long y = r.query(a, b);
            if (y != INF) {
                ans = min(ans, d + y);
                r.update(c, d + y);
            }
            l.update(c, d);
        } else if (b == n - 1) {
            long long x = l.query(a, b);
            if (x != INF) {
                ans = min(ans, x + d);
                l.update(c, x + d);
            }
            r.update(c, d);
        } else {
            long long x = l.query(a, b), y = r.query(a, b);
            ans = min(ans, x + y + d);
            if (x != INF) {
                l.update(c, x + d);
            }
            if (y != INF) {
                r.update(c, y + d);
            }
        }
    }
    cout << (ans == INF ? -1 : ans);
    return 0;
}
