#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const long long INF = 1E18;
vector<int> g[N];
vector<long long> dp[N], dp2[N][N], c;
int p[N], d[N], w[N], s[N], sz[N];
int k;

void dfs(int u) {
  s[u] = d[u] * w[u];
  sz[u] = 1;
  for (int v : g[u]) {
    d[v] += d[u];
    dfs(v);
    w[u] += w[v];
    s[u] += s[v];
    sz[u] += sz[v];
  }
}

void partition(const vector<long long> &a, const vector<long long> &b, const int &z) {
  for (int i = 0; i <= k; i++) c[i] = INF;
  for (int i = 0; i <= min(z, k); i++)
    for (int j = 0; i + j <= min(z, k); j++)
      c[i + j] = min(c[i + j], a[i] + b[j]);
}

void calc_dp(int u) {
  for (int v : g[u]) {
    calc_dp(v);
    partition(dp[u], dp2[u][v], sz[u] - 1);
    swap(c, dp[u]);
  }
  int a = 0;
  for (int i = 1; i <= min(k, sz[u]); i++) {
    int b = dp[u][i];
    dp[u][i] = a + s[u] - d[u] * w[u];
    a = b;
  }
  int x = u;
  while (x) {
    x = p[x];
    for (int v : g[u]) {
      partition(dp2[x][v], dp2[x][u], sz[u] - 1);
      swap(c, dp2[x][u]);
    }
    for (int i = 1; i <= min(k, sz[u]); i++)
      dp2[x][u][i] = min(dp2[x][u][i], dp[u][i] - (s[u] - d[x] * w[u]));
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n >> k;
  ++k, c.resize(k + 1);
  for (int i = 0; i <= n; i++) 
    dp[i].resize(k + 1, INF), dp[i][0] = 0;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      dp2[i][j].resize(k + 1, INF), dp2[i][j][0] = 0;
  for (int i = 1; i <= n; i++) {
    cin >> w[i] >> p[i] >> d[i];
    g[p[i]].push_back(i);
  }
  dfs(0);
  calc_dp(0);
  cout << dp[0][k] << '\n';
  return 0; 
}
