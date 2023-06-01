#include "secret.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mid, v;

void dc(int l, int r, int a[]) {
    if (l > r) return;
    int m = l + r >> 1;
    for (int i = l; i <= r; i++)
        v[i][i] = a[i];
    for (int i = l; i <= m; i++)
        for (int j = m + 1; j <= r; j++)
            mid[i][j] = m;
    for (int i = m - 1; i >= l; i--)
        v[i][m] = Secret(a[i], v[i + 1][m]);
    for (int i = m + 2; i <= r; i++)
        v[m + 1][i] = Secret(v[m + 1][i - 1], a[i]);
    dc(l, m - 1, a);
    dc(m + 1, r, a);
}

void Init(int n, int a[]) {
    mid = v = vector<vector<int>> (n, vector<int> (n, -1));
    dc(0, n - 1, a);
}

int Query(int l, int r) {
    if (v[l][r] != -1) return v[l][r];
    int m = mid[l][r];
    return Secret(v[l][m], v[m + 1][r]);
}
