#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Sparse Table for finding static range queries of monoid operations (in this case min).
 * Time: O(1) query, O(N * log N) construction.
 * Memory O(N * log N)
 */

struct SparseTable{
  int n;
  vector<vector<int>> t;
  SparseTable() {}
  SparseTable(const vector<int> &a) {
    n=(int)a.size();
    int lg=31-__builtin_clz(n);
    t.assign(lg+1,vector<int>(n,1e9));
    t[0]=a;
    for(int i=0;i<lg;i++)
      for(int j=0;j+(2<<i)<=n;j++)
        t[i+1][j]=min(t[i][j],t[i][j+(1<<i)]);
    }
    int query(int l,int r){
      int lg=31-__builtin_clz(r-l+1);
      return min(t[lg][l], t[lg][r-(1<<lg)+1]);
    }
};
