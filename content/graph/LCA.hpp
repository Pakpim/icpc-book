/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: LCA
 */

vi adj[MX];
int up[MX][L+1], lvl[MX];

void dfs(int u, int prt) {
  lvl[u] = lvl[prt] + 1;
  up[u][0] = prt;
  rep(i, 1, L) up[u][i] = up[up[u][i-1]][i-1];
  for (auto v : adj[u]) {
    if (v == prt) continue;
    dfs(v, u);
  }
}

int ancestor(int u, int a) {
  rep(i, 0, L) if (a&(1<<i)) u = up[u][i];
  return u;
}

int lca(int a, int b) {
  if (lvl[a] < lvl[b]) swap(a, b);
  a = ancestor(a,lvl[a] - lvl[b]);
  if (a==b) return a;
  repd(i, 0, L) 
    if (up[a][i] != up[b][i]) 
      a = up[a][i], b = up[b][i];
  return up[a][0];
}