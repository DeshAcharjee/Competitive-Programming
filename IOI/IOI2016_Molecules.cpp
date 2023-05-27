#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> find_subset(int l, int u, vector<int> w) {
    int n = w.size();
    vector<pair<int, int>> v;
    vector<int> ret;
    for (int i = 0; i < n; i++) v.push_back({w[i], i});
    sort(v.begin(), v.end());
    int r = 0;
    long long s = 0;
    for (int i = 0; i < n; i++) {
        while (r < n && s < l) s += v[r++].first;
        if (s >= l && s <= u) {
            for (int l = i; l < r; l++) ret.push_back(v[l].second);
            break;
        }
        s -= v[i].first;
    }
    return ret;
}
