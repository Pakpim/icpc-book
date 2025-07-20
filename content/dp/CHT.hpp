/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Convex Hull Container
 */


struct CHT {
  struct Line {
    ll m, c;
    Line (ll _m, ll _c) { m = _m, c = _c; }
    ll eval(ll x) { return m*x + c; }
  };
  deque<Line> dq;
  
  bool check(Line base, Line cur, Line add) {
    return (cur.c - base.c)*(base.m - add.m) < (add.c - base.c)*(base.m - cur.m);
  }

  void insert(ll m, ll c) {
    Line l(m, c);
    while (dq.size() > 1 && !check(dq.end()[-2], dq.back(), l)) dq.pop_back();
    dq.push_back(l);
  }

  ll query(ll x) {
    while (dq.size() > 1 && dq[0].eval(x) < dq[1].eval(x)) dq.pop_front();
    return dq[0].eval(x);
  }
};