#include <bits/stdc++.h>
using namespace std;

/**
 * Author: Pakapim E.
 * Date: 2025-07-20
 * Description: Treap
 */

using ll=long long;
int n,q;
mt19937 rnd;

struct node{
    ll prio,val,sum,mn,mx,cnt=1;
    ll rev=0,lz1=0;
    bool f2=0;
    node *lc=NULL,*rc=NULL; 
    node(ll val) : prio(rnd()),val(val),sum(val),mn(val),mx(val) {}
    void up(node* nwv){
        if (!nwv) return;
        cnt+=nwv->cnt;
        sum+=nwv->sum;
        mx=max(mx,nwv->mx);
        mn=min(mn,nwv->mn);
        return;
    }
    void in(){
        cnt=1;
        sum=val;
        mn=val;
        mx=val;
    }
};

void push (node* nn,node* np){
    if (!nn) return;
    if (np->f2){
        nn->f2=1;
        nn->lz1=np->lz1;
    }
    else nn->lz1+=np->lz1;
    nn->rev^=np->rev;
    return;
}

void uplazy (node* nn){
    if (!nn) return;
    if (nn->rev==1){
        swap(nn->lc,nn->rc);
    }
    if (nn->f2){
        nn->val=0;
        nn->mn=0;
        nn->mx=0;
        nn->sum=0;
    }
    nn->val+=nn->lz1;
    nn->mn+=nn->lz1;
    nn->mx+=nn->lz1;
    nn->sum+=nn->cnt * nn->lz1;
    push(nn->lc,nn);
    push(nn->rc,nn);
    nn->lz1=0;
    nn->f2=0;
    nn->rev=0;
    return;
}

node* mg (node* t1,node* t2){
    uplazy(t1); uplazy(t2);
    if (!t1) return t2;
    if (!t2) return t1;
    if (t2->prio < t1->prio){
        t1->up(t2);
        t1->rc=mg(t1->rc,t2);
        return t1;
    }
    else{
        t2->up(t1);
        t2->lc=mg(t1,t2->lc);
        return t2;
    }
}

void sp (node* nn,node* &l,node* &r,int x,ll idx){
    if (!nn) return;
    uplazy(nn);
    if (idx<=x){
        l=nn;
        node* tg=nn->rc;
        uplazy(nn->lc);
        uplazy(nn->rc);
        nn->rc=NULL; nn->in(); nn->up(nn->lc);
        idx++;
        if (tg && tg->lc) idx+=tg->lc->cnt;
        sp(tg,l->rc,r,x,idx);
        l->up(l->rc);
    }
    else{
        r=nn;
        node* tg=nn->lc;
        uplazy(nn->lc);
        uplazy(nn->rc);
        nn->lc=NULL; nn->in(); nn->up(nn->rc);
        idx--;
        if(tg && tg->rc) idx-=tg->rc->cnt;
        sp(tg,l,r->lc,x,idx);
        r->up(r->lc);
    }
    return;
}