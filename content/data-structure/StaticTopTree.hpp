#pragma once

/**
 * Author: Pakapim E.
 * Date: 2025-07-20
 * Description: Static Top Tree.
 */

#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const ll N=2e5+5,M=998244353;
vector<ll> g[N];
vector<ll> path[N];
ll par[N],a[N],sz[N],hv[N],top[N],bot[N];

struct node{
    ll m,c,k;
    node *par,*lc,*rc;
    bool s;
    node (): m(0), c(0), k(0), par(NULL), lc(NULL), rc(NULL), s(0) {}
    node (bool s): m(0), c(0), k(0), par(NULL), lc(NULL), rc(NULL), s(s) {}
    node (bool s,ll k): m(0), c(0), k(1), par(NULL), lc(NULL), rc(NULL), s(s) {}
    node (bool s,ll m,ll c): m(m), c(c), k(0), par(NULL), lc(NULL), rc(NULL), s(s) {}
};

node *pt[N],*com[N],*rake[N];

node* build_comp (int l,int r,int nt,int nb,node* np){
    if (l==r){
        int nn=path[nb][l];
        pt[nn]=new node(1,rake[nn]->k,a[nn]);
        rake[nn]->par=pt[nn];
        pt[nn]->par=np;
        pt[nn]->lc=rake[nn];
        return pt[nn];
    }
    node *re=new node(1);
    int mid=(l+r)/2;
    re->lc=build_comp(l,mid,nt,nb,re);
    re->rc=build_comp(mid+1,r,nt,nb,re);
    re->c=(re->rc->c+((re->lc->c*re->rc->m)%M))%M;
    re->m=(re->lc->m*re->rc->m)%M;
    re->par=np;
    return re;
}

node* build_rake(int l,int r,int nr,node* np){
    node *re=new node(0);
    if (l>r){
        re->k=1;
    }
    else if (l==r){
        int nn=g[nr][l];
        if (nn==hv[nr]) re->k=1;
        else{
            com[nn]=build_comp(0,path[bot[nn]].size()-1,nn,bot[nn],re);
            // cout << " comp " << nn << " : " << com[nn]->m << ' ' << com[nn]->c << '\n';
            re->lc=com[nn];
            re->k=com[nn]->c;
        }
    }
    else{
        int mid=(l+r)/2;
        re->lc=build_rake(l,mid,nr,re);
        re->rc=build_rake(mid+1,r,nr,re);
        re->k=(re->lc->k*re->rc->k)%M;
    }
    re->par=np;
    return re;
}


void dfs (int nn){
    sz[nn]=1;
    int mx=0;
    for (auto e:g[nn]) {
        dfs(e);
        sz[nn]+=sz[e];
        if (sz[e]>mx){
            mx=sz[e];
            hv[nn]=e;
        }
    }
    if (!hv[nn]){
        path[nn].emplace_back(nn);
        top[nn]=nn;
        bot[nn]=nn;
    }
    else{
        path[bot[hv[nn]]].emplace_back(nn);
        top[bot[hv[nn]]]=nn;
        bot[nn]=bot[hv[nn]];
    }
    rake[nn]=build_rake(0,g[nn].size()-1,nn,NULL);
    // cout << " rake " << nn << " : " << rake[nn]->k << '\n';
}