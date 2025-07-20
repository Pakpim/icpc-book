/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Rooted Tree Isomorphism Check
 */

const int MX = 1e5 + 3;
 
vi adj[2][MX];
map<vector<int>, int> mp;
int cnt;
 
int dfs(int i, int u, int prt) {
  vector<int> m;
  for (auto v : adj[i][u]) {
    if (v == prt) continue;
    m.pb(dfs(i, v, u));
  }
  sort(all(m));
  if (!mp.count(m)) mp[m] = ++cnt;
  return mp[m];
}
 
void solve() {
  int n; cin >> n;
  rep(j, 2) rep(i, 2, n) {
    int u, v; cin >> u >> v;
    adj[j][u].pb(v); adj[j][v].pb(u);
  }
  cout << (dfs(0, 1, 0) == dfs(1, 1, 0) ? "YES" : "NO") << nl;
  //clear previous testcase
  rep(j, 2) rep(i, 1, n) adj[j][i].clear();
  mp.clear();
  cnt = 0;
}
