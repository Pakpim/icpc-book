#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Li-Chao Tree.
 */

const int N = 1<<18;
 
pll seg[N<<1];
ll a[N], qs[N], mqs[N];
 
ll f(pll p, ll x) {
    return p.st*x + p.nd;
}
 
void clr(int l, int r, int idx) {
    seg[idx] = {0, -1e18};
    if (l==r) return;
    int m = (l+r)/2;
    clr(l, m, 2*idx);
    clr(m+1, r, 2*idx+1);
}
 
void update(int l, int r, pll p, int idx) {
    int m = (l+r)/2;
    bool lef = f(p, l) > f(seg[idx], l);
    bool mid = f(p, m) > f(seg[idx], m);
    if (mid) swap(seg[idx], p);
    if (l==r) return;
    if (lef!=mid) update(l, m, p, 2*idx);
    else update(m+1, r, p, 2*idx+1);
}
 
ll query(int l, int r, int x, int idx) {
    if (l==r) return f(seg[idx], x);
    int m = (l+r)/2;
    if (x <= m) return max(query(l, m, x, 2*idx), f(seg[idx], x));
    else return max(query(m+1, r, x, 2*idx+1), f(seg[idx], x));
}
