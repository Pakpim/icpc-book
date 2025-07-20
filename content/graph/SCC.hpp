#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Strongly Connected Component.
 */

vi adj[MX], rev[MX];
int comp[MX], cnt;
bool vis[MX];
stack<int> order;

void dfs(int i) {
  if (vis[i]) return;
  vis[i] = 1;
  trav(j, adj[i]) dfs(j);
  order.push(i);
}

void dfs2(int i, int c) {
  if (comp[i]) return;
  comp[i] = c;
  for (auto j : rev[i]) dfs2(j, c);
} 

rep(i, 1, M) dfs(i);
while (!order.empty()) dfs2(order.top(), ++cnt), order.pop();