/**
 * Author: ???
 * Date: 2025-07-20
 * Description: Bridge
 */

vi adj[MX];
int disc[MX], low[MX], s[MX], t;
ll ans;
map<pii, pii> bridge;
 
void find_bridge(int u, int prt, int n) {
  disc[u] = low[u] = ++t, s[u] = 1;
  for (auto v : adj[u]) {
    if (v == prt) continue;
    if (!disc[v]) {
      find_bridge(v, u, n);
      if (disc[u] < low[v]) ckmax(ans, (ll)s[v]*(n-s[v]));
      s[u] += s[v];
    }
    ckmin(low[u], low[v]);
  }
}