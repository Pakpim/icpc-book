/**
 * Author: ???
 * Date: 2025-07-20
 * Description: Hierholzer Algorithm for finding Eulerian Circuit
 */

void dfs(int u) {
  while (!adj[u].empty()) {
    auto [v, idx] = adj[u].back(); adj[u].pop_back();
    if (walk[idx]) continue;
    walk[idx] = 1;
    dfs(v);
    ans[++c] = idx;
  }
}