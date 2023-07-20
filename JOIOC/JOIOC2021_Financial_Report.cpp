#include <bits/stdc++.h>
 
using namespace std;

struct SegmentTree {
  vector<int> T;
  int n;
  SegmentTree(int n_) : n(n_) {
    T.resize(n << 1);
  }
  void upd(int u, int x) {
    for (u += n; u > 0; u >>= 1) T[u] = max(T[u], x);
  }
  void upd2(int u) {
    for (T[u += n] = 0; u >>= 1;) T[u] = max(T[u << 1], T[u << 1 | 1]);
  }
  int qry(int l, int r) {
    int x = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = max(x, T[l++]);
      if (r & 1) x = max(x, T[--r]); 
    }
    return x;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, d;
  cin >> n >> d;
  vector<int> a(n), v(n);
  for (int i = 0; i < n; i++) cin >> a[i], v[i] = a[i];
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int &x : a) x = lower_bound(v.begin(), v.end(), x) - v.begin();
  SegmentTree T(n);
  priority_queue<int, vector<int>, greater<int>> pq;
  deque<int> q;
  int ans = 0, dp;
  for (int i = 0; i < n; i++) {
    if (i >= d) {
      while (pq.size() && pq.top() < q.front()) {
        T.upd2(pq.top());
        pq.pop();
      }
    }
    T.upd(a[i], dp = T.qry(0, a[i]) + 1);
    ans = max(ans, dp);
    while (q.size() && q.back() > a[i]) q.pop_back();
    q.push_back(a[i]);
    if (i >= d) {
      pq.push(a[i - d]);
      if (q.size() && q.front() == a[i - d]) q.pop_front();
    }
  }
  cout << ans << '\n';
  return 0;
}
