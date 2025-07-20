/**
 * Author: MIT, https://codeforces.com/blog/entry/90690, Adam Soltan
 * Description: Statistics on a mod'ed arithmetic sequence.
 * Time: O(\log m)
 * Status: minBetween tested for m <= 50.
 */
#pragma once

#include "Euclid.h"

ll cdiv(ll x, ll y) { return x / y + ((x ^ y) > 0 && x % y); }

// min (ax + b) % m for 0 <= x <= n
ll minRemainder(ll a, ll b, ll m, ll n) {
	assert(a >= 0 && m > 0 && b >= 0 && n >= 0);
	a %= m, b %= m; n = min(n, m - 1);
	if (a == 0) return b;
	if (b >= a) {
		ll ad = cdiv(m - b, a);
		n -= ad; if (n < 0) return b;
		b += ad * a - m;
	}
	ll q = m / a, m2 = m % a;
	if (m2 == 0) return b;
	if (b / m2 > n / q) return b - n / q * m2;
	n -= b / m2 * q; b %= m2;
	ll y2 = (n * a + b) / m;
	ll x2 = cdiv(m2 * y2 - b, a);
	if (x2 * a - m2 * y2 + b >= m2) --x2; 
	return minRemainder(a, b, m2, x2);
}

// min x >= 0 s.t. l <= (ax + b) % m <= r
ll minBetween(ll a, ll b, ll m, ll l, ll r) {
  ll x, y, g = euclid(a, m, x, y);
  if (g > 1)
    return minBetween(a/g,b/g,m/g,l/g+(l%g>b%g),r/g-(r%g<b%g));
  if (l > r) return -1; // no solution
  if ((x %= m) < 0) x += m;
  ll b2 = (l - b) * x % m;
  return minRemainder(x, b2 < 0 ? b2 + m : b2, m, r - l);
}