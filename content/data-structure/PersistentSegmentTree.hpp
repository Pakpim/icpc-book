#include "../template/Header.hpp"

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Persistent Segment Tree
 */

const int N = 1<<18;
 
struct node {
    int lc, rc;
    ll val;
} seg[20*N];
int root[N], cnt, a[N];
 
void update(int &cur, int l, int r, int x, ll val) {
    cnt++;
    seg[cnt] = seg[cur];
    cur = cnt;
 
    if (l==r) {
        seg[cur].val = val;
        return;
    }
    int mid = (l+r)/2;
    if (x <= mid) {
        update(seg[cur].lc, l, mid, x, val);
    }
    else {
        update(seg[cur].rc, mid+1, r, x, val);
    }
    seg[cur].val = seg[seg[cur].lc].val + seg[seg[cur].rc].val;
}
 
ll query(int cur, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return seg[cur].val;
 
    int mid = (l+r)/2;
    return query(seg[cur].lc, l, mid, ql, qr) + query(seg[cur].rc, mid+1, r, ql, qr);
}
 
void solve() {
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        update(root[1], 1, n, i, a[i]);
    }
 
    int sz = 1;
 
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            ll k, a, x; cin >> k >> a >> x;
            update(root[k], 1, n, a, x);
        }
        if (op == 2) {
            ll k, a, b; cin >> k >> a >> b;
            cout << query(root[k], 1, n, a, b) << '\n';
        }
        if (op == 3) {
            ll k; cin >> k;
            root[++sz] = root[k];
        }
    }
}