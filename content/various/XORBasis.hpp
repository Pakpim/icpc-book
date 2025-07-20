/**
 * Author: Pasin P.
 * Date: 2025-07-20
 * Description: XOR Basis
 */


template<int BIT>
struct XOR_basis {
  vector<ll> basis;
  int mSize = 0;
  XOR_basis() { basis.assign(BIT, 0); }
  //Insert v into basis, if v is already in the span of the basis, do nothing. O(BIT)
  void insert(ll v) {
    for (int i = BIT-1; i >= 0; --i) {
      if (!(v>>i & 1)) continue; 
      if (basis[i]) v ^= basis[i];
      else {basis[i] = v, mSize++; return; }
    }
  }
  int size() { return mSize; }
  //Perform row reduction to make basis in reduced row echelon form in O(BIT^2)
  void reduce() {
    for (int i = BIT-1; i >= 0; --i) {
      for (int j = i-1; j >= 0; --j) {
        if (!basis[j]) continue;
        if (basis[i]>>j & 1) basis[i] ^= basis[j];
      }
    }
  }
  //Check whether v is in span of the current basis in O(BIT)
  bool in_span(ll v) {
    for (int i = BIT-1; i >= 0; --i) {
      if (!(v>>i & 1)) continue;
      v ^= basis[i];
    }
    return (v == 0);
  }
  ll &operator[] (int i) { return basis[i]; }
};