/**
 * Author: Pakapim E.
 * Date: 2025-07-20
 * Description: Alien Trick
 */

#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using tl=__int128_t;
using db=double;
const ll N=500005;
ll c[N],sum[N];
deque<tuple<ll,ll,int>> dq;

ll minPenguinValue(int n, int m, vector<int> a){
    ll l=0,r=2e18,re;
    for (int i=1;i<=n;i++){
        sum[i]=sum[i-1]+ll(a[i-1]);
        c[i]=c[i-1]+sum[i]*ll(a[i-1]);
    }
    while (l<=r){
        ll mid=l+(r-l)/2;
        while (!dq.empty()) dq.pop_back();
        dq.emplace_back(0,0,0);
        for (int i=1;i<=n;i++){
            while (dq.size()>1){
                auto [m1,c1,u1]=dq.front();
                dq.pop_front();
                auto [m2,c2,u2]=dq.front();
                if (c2-c1>=sum[i]*(m1-m2)){
                    dq.emplace_front(m1,c1,u1);
                    break;
                }
            }
            auto [nm,nc,nu]=dq.front();
            ll nv=nm*sum[i]+nc+c[i]+mid;
            ll m3=-sum[i],c3=-c[i]+sum[i]*sum[i]+nv;
            if (i==n){
                if (nu+1>m) l=mid+1;
                else{
                    re=nv-m*mid;
                    r=mid-1;
                }
            }
            while (dq.size()>1){
                auto [m2,c2,u2]=dq.back();
                dq.pop_back();
                auto [m1,c1,u1]=dq.back();
                if (db(c3-c1)/db(m1-m3)<=db(c3-c2)/db(m2-m3)){
                    dq.emplace_back(m2,c2,u2);
                    break;
                }
            }
            dq.emplace_back(m3,c3,nu+1);
        }
    }
    return re;
}