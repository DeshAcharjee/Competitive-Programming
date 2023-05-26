#include <bits/stdc++.h>
using namespace std;

struct line {
    long long m, c;
    int id;
    long long value(int x) {
        return m * x + c;
    }
    long double isec(const line &l) {
        return (c - l.c) / (long double) (l.m - m);
    }
};

struct CHT {
    deque<line> cht;
    void insert(line l) {
        if (cht.empty()) {
            cht.push_back(l);
            return;
        }
        if (cht.back().m == l.m) {
            cht.back() = l;
            return;
        }
        while (cht.size() >= 2 && cht.back().isec(*next(cht.rbegin())) >= (cht.back()).isec(l))
            cht.pop_back();
        cht.push_back(l);
    }
    pair<long long, int> query(int x) {
        while (cht.size() >= 2 && cht[0].value(x) <= cht[1].value(x))
            cht.pop_front();
        return {cht[0].value(x), cht[0].id};
    }
} cht[201];

int pre[100001], par[201][100001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    long long ans;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> pre[i], pre[i] += pre[i - 1];
    for (int i = 1; i <= n; i++) {
        long long prev = 0;
        for (int j = 1; j <= min(k, i - 1); j++) {
            auto [x, y] = cht[j].query(pre[i]);
            if (i == n && j == k) ans = x;
            par[j][i] = y;
            cht[j].insert({pre[i], prev - (long long) pre[i] * pre[i], i});
            prev = x;
        }
        if (k >= i) cht[i].insert({pre[i], prev - (long long) pre[i] * pre[i], i});
    }
    cout << ans << '\n';
    for (int x = par[k][n], i = k; i >= 1; i--, x = par[i][x])
        cout << x << ' ';
}
