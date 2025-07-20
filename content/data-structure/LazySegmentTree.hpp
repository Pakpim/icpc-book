#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Segment Tree with Lazy Propagation
 */

template<class Node, class Tag>
struct LazySegTree{
  int n;
  vector<Node> t;
  vector<Tag> lz;
  LazySegTree() {}
  LazySegTree(int n, Node v=Node()) {init(n, v);}
  template<class T>
  LazySegTree(const vector<T> &a) {init(a);}
  void init(int n, Node v=Node()) {init(vector<Node>(n, v));}
  template<class T>
  void init(const vector<T> &a) {
    n=sz(a);
    t.assign((4<<(31-__builtin_clz(n)))+1, Node());
    lz.assign((4<<(31-__builtin_clz(n)))+1, Tag());
    function<void(int, int, int)> build=[&](int l, int r, int i){
      if (l==r) return void(t[i]=a[l-1]);
      int m=(l+r)/2;
      build(l,m,2*i);
      build(m+1,r,2*i+1);
      pull(i);
    };
    build(1,n,1);
  }
  void pull(int i) {
    t[i]=t[2*i]+t[2*i+1];
  }
  void apply(int l,int r,int i,const Tag &v) {
    t[i].apply(l,r,v);
    lz[i].apply(l,r,v);
  }
  void push(int l, int r, int i) {
    int m=(l+r)/2;
    apply(l,m,2*i, lz[i]);
    apply(m+1,r,2*i+1, lz[i]);
    lz[i] = Tag();
  }
  void modify(int l, int r, int i, int x, const Node &v) {
    if (x<l||x>r) return;
    if (l==r) return void(t[i]=v);
    int m=(l+r)/2;
    push(l,r,i);
    modify(l,m,2*i,x,v);
    modify(m+1,r,2*i+1,x,v);
    pull(i);
  }
  void modify(int x, const Node &v) { modify(1,n,1,x,v); }
  void update(int l, int r, int x, int y, int i, const Tag &v) {
    if (y<l||x>r) return;
    if (x<=l&&r<=y) return apply(l, r, i, v);
    int m=(l+r)/2;
    push(l, r, i);
    update(l, m, x, y, 2*i, v);
    update(m+1, r, x, y, 2*i+1, v);
    pull(i);
  }
  void update(int x, int y, const Tag &v) { update(1, n, x, y, 1, v); }
  void update(int x, const Tag &v) { update(1, n, x, x, 1, v); }
  Node query(int l, int r, int x, int y, int i) {
    if (y<l || x>r) return Node();
    if (x<=l&&r<=y) return t[i];
    int m=(l+r)/2;
    push(l, r, i);
    return query(l, m, x, y, 2*i)+query(m+1, r, x, y, 2*i+1);
  }
  Node query(int x, int y) { return query(1, n, x, y, 1); }
  Node query(int x) { return query(1, n, x, x, 1); }
};
struct Tag{
  ll val;
  Tag(ll _val=0):val(_val){}
  void apply(int l, int r, const Tag &v) { val+=v.val; }
};
struct Node{
  ll val;
  Node(ll _val=0):val(_val){}
  void apply(int l, int r, const Tag &v) { val+=v.val; }
  friend Node operator+(const Node &lhs, const Node &rhs) {
    return Node(max(lhs.val, rhs.val)); 
  }
};