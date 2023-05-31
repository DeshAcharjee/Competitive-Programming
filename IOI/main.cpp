#include "aliens.h"
#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    bool operator < (const point &p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
};

struct line {
    int m;
    long long c;
    int s;
    long long eval(const int &x) {
        return 1LL * m * x + c;
    }
    bool good(const line &l1, const line &l2) {
        return __int128(l1.c - l2.c) * (l1.m - m) < __int128(c - l1.c) * (l2.m - l1.m);
    }
};

int N;
vector<point> r;

struct CHT {
    deque<line> hull;
    void insert(line l) {
        while (hull.size() > 1 && !l.good(hull.back(), *next(hull.rbegin()))) hull.pop_back();
        hull.push_back(l);
    }
    pair<long long, int> qry(int x) {
        while (hull.size() > 1 && hull[0].eval(x) > hull[1].eval(x)) hull.pop_front();
        return {hull[0].eval(x), hull[0].s};
    }
};

long long sq(int x) {
    return 1LL * x * x;
}

pair<long long, int> aliens(long long lambda) {
   CHT cht;
   cht.insert({-2 * r[0].x, sq(r[0].x) - 2 * r[0].x, 1});
   for (int i = 0; i < N; i++) {
        auto dp = cht.qry(r[i].y);
        dp.first += sq(r[i].y + 1) + lambda;
        if (i == N - 1) return dp;
        cht.insert({-2 * r[i + 1].x, dp.first + sq(r[i + 1].x) - 2 * r[i + 1].x - sq(max(0, r[i].y - r[i + 1].x + 1)), dp.second + 1});
   }
}

long long take_photos(int n, int m, int k, vector<int> R, vector<int> C) {
    vector<point> f;
    r = vector<point> ();
    for (int i = 0; i < n; i++) {
        if (R[i] > C[i]) swap(R[i], C[i]);
        f.push_back({R[i], C[i]});
    }
    sort(f.begin(), f.end());
    r.push_back(f[0]);
    for (int i = 1; i < n; i++) {
        if (r.back().x == f[i].x) {
            r.pop_back();
            r.push_back(f[i]);
        } else if (f[i].y > r.back().y) {
            r.push_back(f[i]);
        }
    }
    N = r.size(), k = min(N, k);
    long long l_ = 0, r_ = 1e11;
    while (l_ < r_) {
        long long m_ = l_ + r_ >> 1;
        if (aliens(m_).second > k) l_ = m_ + 1;
        else r_ = m_ ;
    }
    return aliens(l_).first - l_ * k;
}
