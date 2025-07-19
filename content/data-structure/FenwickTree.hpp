#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Fenwick / Binary Indexed Tree
 * Time: query and update O(\log N)
 * Memory: O(N)
 */

struct fenwick {
  int n;
  vector<int> t;
  fenwick (int n=0) {
    n=_n;
    t.assign(n+1, T{});
  }
  void update(int x, int v) {
    for (int i = x; i <= n; i+=i&-i) t[i] = t[i]+v;
  }
  void update(int l, int r, int v) {
    update(l, v); update(r+1, -v);
  }
  int query(int x) {
    int res = 0;
    for (int i = x; i >= 1; i-=i&-i) res = res+t[i];
    return res;
}
  int query(int l, int r) { return query(r) - query(l-1); }
  //find the first index that sums to >= k
  int find(const T &k) {
    int x = 0;
    int cur = 0;
    for (int i = 1<<(31-__builtin_clz(n)); i > 0; i>>=1)
      if (x+i <= n && cur+t[x+i] < k) x+=i, cur+=t[x];
    return x;
  }
};