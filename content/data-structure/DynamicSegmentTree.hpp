#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Dynamic Segment Tree
 */

const int MX = 1e5 + 3;
 
struct Node {
  ll cnt;
  ll sum;
  Node *lc, *rc;
  Node() {
    sum = cnt = 0;
    lc = rc = nullptr; 
  }
  void createChild() {
    if (lc == nullptr) lc = new Node();
    if (rc == nullptr) rc = new Node();
  }
};
 
Node *root = new Node();
 
void update(ll l, ll r, ll x, ll val, Node *cur) {
  if (l==r) {
    cur -> cnt += val;
    cur -> sum += x*val;
    return;
  }
  ll mid = (l+r)>>1;
  cur -> createChild();
  if (x <= mid) update(l, mid, x, val, cur -> lc);
  else update(mid+1, r, x, val, cur -> rc);
 
  cur->sum = cur->lc->sum + cur->rc->sum;
  cur->cnt = cur->lc->cnt + cur->rc->cnt;
}

// Query function for the Dynamic Segment Tree
pair<ll, ll> query(ll l, ll r, ll ql, ll qr, Node *cur) {
  if (cur == nullptr || ql > r || qr < l) {
    return {0, 0}; // {count, sum}
  }
  
  if (ql <= l && r <= qr) {
    return {cur->cnt, cur->sum};
  }
  
  ll mid = (l + r) >> 1;
  cur->createChild();
  
  auto left_result = query(l, mid, ql, qr, cur->lc);
  auto right_result = query(mid + 1, r, ql, qr, cur->rc);
  
  return {left_result.first + right_result.first, 
          left_result.second + right_result.second};
}

// Wrapper function for easier usage
pair<ll, ll> query(ll ql, ll qr) {
  return query(0, MX - 1, ql, qr, root);
}
 
ll search(ll l, ll r, ll lsum, ll rfreq, ll k, Node *cur) {
  if (l==r) return l;
  ll mid = (l+r)>>1;
  cur -> createChild();
  __int128_t cntMid = lsum + (__int128_t)(mid+1)*rfreq + (cur->lc->sum) + (__int128_t)(mid+1)*(cur->rc->cnt);
  if (cntMid < (__int128_t)(mid+1)*k) return search(l, mid, lsum, rfreq + cur->rc->cnt, k, cur -> lc);
  else return search(mid+1, r, lsum + cur->lc->sum, rfreq, k, cur -> rc);
}
