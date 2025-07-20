/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Unrooted Tree Isomorphism Check
 */

const int MX = 1e5 + 3;
 
vi adj[MX][2];
int sz[MX][2], cnt;
vector<int> centroid[2];
map<vector<int>, int> mp;
 
void find_centroid(int u, int t, int n, int prt=0) {
  bool is_centroid = 1;
  sz[u][t] = 1;
  for (auto v : adj[u][t]) {
    if (v == prt) continue;
    find_centroid(v, t, n, u);
    if (sz[v][t] > n/2) is_centroid = 0;
    sz[u][t] += sz[v][t];
  }
  if (n - sz[u][t] > n/2) is_centroid = 0;
  if (is_centroid) centroid[t].pb(u);
}
 
int dfs(int u, int t, int prt=0) {
  vector<int> m;
  for (auto v : adj[u][t]) {
    if (v == prt) continue;
    m.pb(dfs(v, t, u));
  }
  sort(all(m));
  if (!mp.count(m)) mp[m] = ++cnt;
  return mp[m];
}
 
void solve() {
  int n; cin >> n;
  rep(j, 2) rep(i, 2, n) {
    int u, v; cin >> u >> v;
    adj[u][j].pb(v), adj[v][j].pb(u);
  }
  rep(j, 2) find_centroid(1, j, n);
  bool iso = 0;
  for (auto c0 : centroid[0]) for (auto c1 : centroid[1]) {
    iso |= dfs(c0, 0) == dfs(c1, 1);
  }
  cout << (iso ? "YES" : "NO") << nl;
  rep(j, 2) rep(i, 1, n) adj[i][j].clear();
  rep(j, 2) centroid[j].clear();
