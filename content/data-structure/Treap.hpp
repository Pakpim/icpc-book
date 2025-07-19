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


int main (){
    ios::sync_with_stdio(0); cin.tie(0);
    rnd.seed(time(NULL));
    cin >> n >> q;
    ll v,tm=1;
    cin >> v;
    node *rt=new node(v);
    for (int i=2;i<=n;i++){
        cin >> v;
        node *nw=new node(v);
        rt=mg(rt,nw);
    }
    while (q--){
        int op,l,r,v,x;
        cin >> op;
        switch (op){
        // + l r v
        case 1: {
            cin >> l >> r >> v;
            node *a=NULL,*b=NULL,*c=NULL,*tg=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,r,idx);
            idx=1;
            if (a->lc) idx+=a->lc->cnt;
            sp(a,c,tg,l-1,idx);
            tg->lz1+=v;
            a=mg(c,tg);
            rt=mg(a,b);
            break;
        }
        // change l r v
        case 2: {
            cin >> l >> r >> v;
            node *a=NULL,*b=NULL,*c=NULL,*tg=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,r,idx);
            idx=1;
            if (a->lc) idx+=a->lc->cnt;
            sp(a,c,tg,l-1,idx);
            tg->f2=1;
            tg->lz1=v;
            a=mg(c,tg);
            rt=mg(a,b);
            break;
        }
        // reverse l r
        case 3: {
            cin >> l >> r;
            node *a=NULL,*b=NULL,*c=NULL,*tg=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,r,idx);
            idx=1;
            if (a->lc) idx+=a->lc->cnt;
            sp(a,c,tg,l-1,idx);
            tg->rev^=1;
            a=mg(c,tg);
            rt=mg(a,b);
            break;
        }
        // erase l r
        case 4: {
            cin >> l >> r;
            node *a=NULL,*b=NULL,*c=NULL,*tg=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,r,idx);
            idx=1;
            if (a->lc) idx+=a->lc->cnt;
            sp(a,c,tg,l-1,idx);
            rt=mg(c,b);
            break;
        }
        // insert after idx v
        case 5: {
            cin >> x >> v;
            node *a=NULL,*b=NULL,*c=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,x,idx);
            node *nw=new node(v);
            c=mg(a,nw);
            rt=mg(c,b);
            break;
        }
        // sum l r
        case 6: {
            cin >> l >> r;
            node *a=NULL,*b=NULL,*c=NULL,*tg=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,r,idx);
            idx=1;
            if (a->lc) idx+=a->lc->cnt;
            sp(a,c,tg,l-1,idx);
            // db(tg);
            // cout << '\n';
            cout << tg->sum << '\n';
            a=mg(c,tg);
            rt=mg(a,b);
            break;
        }
        // min l r
        case 7: {
            cin >> l >> r;
            node *a=NULL,*b=NULL,*c=NULL,*tg=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,r,idx);
            idx=1;
            if (a->lc) idx+=a->lc->cnt;
            sp(a,c,tg,l-1,idx);
            cout << tg->mn << '\n';
            a=mg(c,tg);
            rt=mg(a,b);
            break;
        }
        // max l r
        case 8: {
            cin >> l >> r;
            node *a=NULL,*b=NULL,*c=NULL,*tg=NULL;
            ll idx=1;
            if (rt->lc) idx+=rt->lc->cnt;
            sp(rt,a,b,r,idx);
            idx=1;
            if (a->lc) idx+=a->lc->cnt;
            sp(a,c,tg,l-1,idx);
            cout << tg->mx << '\n';
            a=mg(c,tg);
            rt=mg(a,b);
            break;
        }
        default:
            break;
        }
        // db(rt);
        // cout << "----\n";
    }
}