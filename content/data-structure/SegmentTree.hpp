#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Description: Segment Tree
 */
template<class Node>
struct SegTree {
	int n;
	vector<Node> t;
	SegTree(){};
	SegTree(int n, Node v=Node()) {init(n, v);}
	template<class T>
	SegTree(const vector<T> &a) {init(a);}
	void init(int n, Node v=Node()) {init(vector<Node>(n, v));}
	template<class T>
	void init(const vector<T> &a) {
		n=sz(a);
		t.assign(4<<31-__builtin_clz(n),Node());
		function<void(int, int, int)> build=[&](int l, int r, int i) {
			if (l==r) return void(t[i]=a[l-1]);
			int m = (l+r)/2;
			build(l, m, 2*i);
			build(m+1, r, 2*i+1);
			pull(i);
		};
		build(1, n, 1);
	}
	void pull(int i) {t[i] = t[2*i] + t[2*i+1];}
	void modify(int l, int r, int i, int x, const Node &v) {
		if (x<l || x>r) return;
		if (l==r) return void(t[i]=v);
		int m = (l+r)/2;
		if (x<=m) modify(l, m, 2*i, x, v);
		else modify(m+1, r, 2*i+1, x, v);
		pull(i);
	}
	void modify(int x, const Node &v) {modify(1, n, 1, x, v);}
	template<class T>
	void update(int l, int r, int i, int x, const T &v) {
		if (x<l || x>r) return;
		if (l==r) return void(t[i].apply(l, r, v));
		int m = (l+r)/2;
		if (x<=m) update(l, m, 2*i, x, v);
		else update(m+1, r, 2*i+1, x, v);
		pull(i);
	}
	template<class T>
	void update(int x, const T &v) {update(1, n, 1, x, v);}
	Node query(int l, int r, int i, int x, int y) {
		if (y<l || x>r) return Node();
		if (x<=l && r<=y) return t[i];
		int m = (l+r)/2;
		return query(l, m, 2*i, x, y) + query(m+1, r, 2*i+1, x,y);
	}
	Node query(int x, int y) {return query(1, n, 1, x, y);}
	template<class F>
	int findfirst(int l, int r, int i, int x, int y, const F &f) {
		if (y<l||r<x||!(f(t[i]))) return -1;
		if (l==r) return l;
		int m = (l+r)/2;
		int ret = findfirst(l, m, 2*i, x, y, f);
		if (ret == -1) ret = findfirst(m+1, r, 2*i+1, x, y, f);
		return ret;
	}
	template<class F>
	int findfirst(int x, int y, const F &f) {return findfirst(1, n, 1, x, y, f);}
	template<class F>
	int findlast(int l, int r, int i, int x, int y, const F &f) {
		if (y<l||r<x||!(f(t[i]))) return -1;
		if (l==r) return l;
		int m = (l+r)/2;
		int ret = findlast(m+1, r, 2*i+1, x, y, f);
		if (ret == -1) ret = findlast(l, m, 2*i, x, y, f);
		return ret;
	}
	template<class F>
	int findlast(int x, int y, const F &f) {return findlast(1, n, 1, x, y, f);}
};

struct Node {
    ll val;
	Node(ll x=LLONG_MAX):val(x){}
	void apply(int l, int r, int x) {val = x;}
	friend Node operator+(const Node &lhs, const Node &rhs) {
		return Node(min(lhs.val, rhs.val));
	}
};