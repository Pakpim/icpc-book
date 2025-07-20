/**
 * Author: Adam Soltan
 * Description: Finds a primitive root modulo $p$.
 */
#pragma once

#include "Factor.h"
#include "ModMulLL.h"

mt19937_64 rng(2137);
ll modGen(ll n) {
  map<ll, int> f; factor(n - 1, f); rep:
  ll g = rng() % (n - 1) + 1;
  for (auto [p, _] : f)
    if (modpow(g, (n - 1) / p, n) == 1) goto rep;
  return g;
}