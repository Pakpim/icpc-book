/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: Aho Corasick Automaton
 */

struct AC {
  struct Node {
    ll val = 0, mark = 0;
    vector<int> ch;
    Node() { ch.assign(27, 0); }
  };
  vector<Node> t;
  vector<int> out, link;
  AC () { push_back(); }
  int push_back() {
    t.push_back(Node());
    out.push_back(0);
    link.push_back(0);
    return t.size()-1;
  }
  int insert(const string s) {
    int idx = 0;
    for (auto c : s) {
      int v = (c==' '?26:c-'a');
      if (!t[idx].ch[v]) t[idx].ch[v] = push_back();
      idx = t[idx].ch[v];
    }
    t[idx].mark = 1;
    return idx;
  }
  void compute() {
    queue<int> q; q.push(0);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int c = 0; c < 27; ++c) {
        int v = t[u].ch[c];
        if (!v) t[u].ch[c] = t[link[u]].ch[c];
        else {
          link[v] = u ? t[link[u]].ch[c] : 0;
          out[v] = (t[link[v]].mark ? link[v] : out[link[v]]);
          q.push(v);
        }
      }
    }
  }
  int advance(int idx, char c) {
    int v = (c==' '?26:c-'a');
    while (idx && !t[idx].ch[v]) idx = link[idx]; 
    return t[idx].ch[v];
  }
};

string p[MX];
ll idx[MX], po[MX];

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(NULL);
  int n, m, k; cin >> n >> m >> k;
  AC aho;
  string s; getline(cin, s);
  for (int i = 1; i <= n; ++i) getline(cin, p[i]), idx[i] = aho.insert(p[i]); 
  aho.compute();
  po[0] = 1;
  for (int i = 1; i <= m; ++i) po[i] = (po[i-1] * 173) % MOD;
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    aho.t[idx[u]].val = (aho.t[idx[u]].val + po[i]) % MOD;
    aho.t[idx[v]].val = (aho.t[idx[v]].val - po[i]) % MOD;
  }
  getline(cin, s);
  for (int i = 1; i <= k; ++i) {
    string s; getline(cin, s);
    ll val = 0, u = 0;
    for (auto c : s) {
      u = aho.advance(u, c);
      for (int v = u; v; v = aho.out[v]) val = (val + aho.t[v].val) % MOD;
    }
    cout << (val ? "no" : "yes") << nl;
  }
}