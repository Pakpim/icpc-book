#pragma once

/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Binary Trie
 */

template<int BIT>
struct BinaryTrie {
  struct Node {
    array<int, 2> ch;
    int cnt;
    Node() : ch{-1, -1}, cnt(0) {}
  };
  vector<Node> t;
  BinaryTrie() : t{Node()} {}
  int new_node() {
    t.emplace_back(Node());
    return t.size()-1;
  }
  int size() { return t[0].cnt; }
  bool empty() { return size()==0; }
  void insert(ll val, int k=1) {
    int cur = 0;
    t[cur].cnt += k;
    for (int i = BIT-1; i >= 0; --i) {
      int b = val>>i & 1;
      if (t[cur].ch[b] == -1) t[cur].ch[b] = new_node();
      cur = t[cur].ch[b];
      t[cur].cnt += k;
    }
  }
  void erase(ll val, int k=1) {
    if (count(val) < k) return;
    int cur = 0;
    t[cur].cnt -= k;
    for (int i = BIT-1; i >= 0; --i) {
      int b = val>>i & 1;
      cur = t[cur].ch[b];
      t[cur].cnt -= k;
    }
  }
  void clear() {
    t = {Node};
  }
  ll get_max(ll val) {
    if (empty()) return LLONG_MIN;
    int cur = 0, ans = 0;
    for (int i = BIT-1; i >= 0; --i) {
      int b = val>>i & 1;
      if (t[cur].ch[!b] != -1 && t[t[cur].ch[!b]].cnt > 0) cur = t[cur].ch[!b], ans <<= 1, ans++;
      else cur = t[cur].ch[b], ans <<= 1;
    }
    return ans;
  }
  ll get_min(ll val) {
    if (empty()) return LLONG_MAX;
    int cur = 0, ans = 0;
    for (int i = BIT-1; i >= 0; --i) {
      int b = val>>i & 1;
      if (t[cur].ch[b] != -1 && t[t[cur].ch[b]].cnt > 0) cur = t[cur].ch[b], ans <<= 1, ans++;
      else cur = t[cur].ch[!b], ans <<= 1;
    }
    return ans;
  }
  int count(ll val) {
    int cur = 0;
    for (int i = BIT-1; i >= 0; --i) {
      int b = val>>i & 1;
      if (t[cur].ch[b] == -1) return false;
      cur = t[cur].ch[b];
    }
    return t[cur].cnt;
  }
};

