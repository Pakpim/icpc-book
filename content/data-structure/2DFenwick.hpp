#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: 2D Fenwick Tree. Requires that elements to be updated is known in advance. 
 * Note that X is not compressed. 
 * Time: query and update O(\log^2 N)
 * Memory: O(N \log N) (i guess)
 */

struct TD_fenwick {
  int n;
  vector<vector<int>> vals, t;
  TD_fenwick(int n, vector<pii> &v): n(n), vals(n+1), t(n+1) {
    for (int i = 1; i <= n; ++i) vals[i].push_back(0);
    sort(all(v), [&](pii a, pii b){ return a.second < b.second; });
    for (auto [x, y] : v) for (; x <= n; x += x&-x) if (vals[x].back() != y) vals[x].push_back(y);
    for (int i = 1; i <= n; ++i) t[i].resize(vals[i].size()+3);
  }
  inline int cp(int i, int x) {
    return upper_bound(all(vals[i]), x) - vals[i].begin();
  }
  void update(int x, int y, int val) {
    for (int i = x; i <= n; i += i&-i) {
      for (int j = cp(i, y); j < t[i].size(); j += j&-j) t[i][j] += val;
    }
  }
  int query(int x, int y) {
    int res = 0;
    for (int i = x; i >= 1; i -= i&-i) {
      for (int j = cp(i, y); j >= 1; j -= j&-j) res += t[i][j];
    }
    return res;
  }
  int query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x2, y1-1) - query(x1, y2) + query(x1, y1-1);
  }
};