#pragma once
#include "../template/Header.hpp"

/**
 * Author: Pakapim E.
 * Date: 2025-07-20
 * Description: Fast Fourier transform
 * Time: $O(N \log N)$
 */

using ll = long long;
using poly = vector<ll>;
const ll M=998244353;
ll pr=3,inv_pr,m;
 
ll bp(ll a,ll b){
    ll re=1ll;
    while (b){
        if (b&1) re=(re*a)%M;
        a=(a*a)%M;
        b>>=1;
    }
    return re;
}
 
void fft (poly &a, bool inv){
    ll n=a.size();
    if (n==1) return;
    poly o(n>>1ll),e(n>>1ll);
    for (ll i=0;i<n;i+=2){
        e[i>>1ll]=a[i];
        o[i>>1ll]=a[i+1];
    }
    fft(e,inv);
    fft(o,inv);
    ll w = bp(pr,((M-1ll)/n));
    if (inv) w = bp(inv_pr,((M-1ll)/n));
    for (ll i=0;i<(n>>1ll);i++){
        a[i]=(e[i]+((bp(w,i)*o[i])%M))%M;
        a[i+(n>>1ll)]=((e[i]-((bp(w,i)*o[i])%M))%M+M)%M;
    }
}
 
poly mul (poly a, poly b){
    poly re;
    ll n=1;
    while (n<a.size()+b.size()) n<<=1ll;
    a.resize(n);
    b.resize(n);
    fft(a,0);
    fft(b,0);
    re.resize(n);
    for (ll i=0;i<n;i++){
        re[i]=(a[i]*b[i])%M;
    }
    fft(re,1);
    for (auto &e:re) e=(e*bp(n,M-2))%M;
    return re;
}
 
poly inv(poly &a){
    poly re;
    re.emplace_back(bp(a[0],M-2));
    poly b;
    for (int n=1;n<a.size();n<<=1){
        while (b.size()<min(int(a.size()),n*2)) b.emplace_back(a[b.size()]);
        poly tmp = mul(re,re);
        tmp = mul(tmp,b);
        for (int i=0;i<n;i++){
            re[i]=(((re[i]*2)%M-tmp[i])%M+M)%M;
        }
        for (int i=0;i<n;i++){
            re.emplace_back((M-tmp[i+n])%M);
        }
    }
    return re;
}
 
poly sqrtp(poly &a){
    poly re;
    re.emplace_back(1); // need re[0]^2 == a[0], but now a[0] == 1
    poly b;
    for (int n=1;n<a.size();n<<=1){
        while (b.size()<min(int(a.size()),n*2)) b.emplace_back(a[b.size()]);
        for (int i=0;i<n;i++) re.emplace_back(0);
        poly tmp = mul(b,inv(re));
        for (int i=0;i<n*2;i++){
            re[i]=(re[i]+tmp[i])%M;
            re[i]=(re[i]*bp(2,M-2))%M;
        }
    }
    return re;
}