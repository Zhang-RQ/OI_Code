#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=2E5+10;
struct node{
    int son[2],val;
}t[MAXN<<6];
struct Query{
    int l,r,x,tl,tr,id;
    Query(){}
    Query(int _,int __,int ___,int ____,int _____,int ______){l=_;r=__;x=___;tl=____;tr=_____;id=______;}
}Q[MAXN];
struct opt{
    int t,s,v;
    bool operator < (const opt &rhs) const {return s<rhs.s;}
    opt(){}
    opt(int _,int __,int ___){t=_;s=__;v=___;}
}O[MAXN],tmpL[MAXN],tmpR[MAXN];
int rt[MAXN],cnt,ans[MAXN],id[MAXN];
int num[MAXN],ntot,idd[MAXN];
int n,m,cntQ,cntO,day;
void insert(int pos,int val)
{
    rt[pos]=++cnt;
    int x=rt[pos],now,_x=rt[pos-1];
    for(int j=18;~j;j--)
    {
        now=(val>>j)&1;
        t[x]=t[_x];t[x].val++;
        t[x].son[now]=++cnt;
        x=t[x].son[now];_x=t[_x].son[now];
    }
    assert(cnt<MAXN<<6);
    t[x]=t[_x];t[x].val++;
}
int query(int l,int r,int val)
{
    int ret=0,x=rt[r],_x=rt[l],now;
    for(int j=18,siz;~j;j--)
    {
        now=((val>>j)&1)^1;
        siz=t[t[x].son[now]].val-t[t[_x].son[now]].val;
        if(siz)  x=t[x].son[now],_x=t[_x].son[now],ret|=now<<j;
        else x=t[x].son[!now],_x=t[_x].son[!now],ret|=(now^1)<<j;
    }
    return ret^val;
}
int Lower(int val)
{  
    int l=1,r=ntot,ret=0;  
    while(l<=r) 
    {  
        int mid=(l+r)>>1;  
        if(num[mid]<=val) 
        {  
            ret=mid;l=mid+1;  
        }  
        else r=mid-1;  
    }  
    return ret;  
}  
  
void solve(int ml,int mr,int tot)
{
    ntot=0;cnt=0;
    for(int i=ml;i<=mr;i++)
    {
        ++ntot;
        insert(ntot,O[i].v);
        num[ntot]=O[i].s;
    }
    for(int i=1,L,R;i<=tot;i++)
    {
        L=Lower(Q[id[i]].l-1);R=Lower(Q[id[i]].r);
        ans[Q[id[i]].id]=max(ans[Q[id[i]].id],query(L,R,Q[id[i]].x));
    }
}
void Divide_Conquer(int ml,int mr,int tl,int tr,int tot) //solving queries idd[1]...idd[tot]
{
    if(ml>mr||tot==0) return;
    int tt=0,mid=(tl+tr)>>1,ttl=0,ttr=0;
    for(int i=1;i<=tot;i++) 
        if(Q[idd[i]].tl<=tl&&tr<=Q[idd[i]].tr) 
            id[++tt]=idd[i];
    solve(ml,mr,tt);
    for(int i=ml;i<=mr;i++)
        if(O[i].t<=mid) tmpL[++ttl]=O[i];
        else tmpR[++ttr]=O[i];
    for(int i=1;i<=ttl;i++)
        O[ml+i-1]=tmpL[i];
    for(int i=1;i<=ttr;i++)
        O[ml+ttl+i-1]=tmpR[i];
    if(tl==tr) return;
    tt=0;
    for(int i=1;i<=tot;i++)
    {
        if(Q[idd[i]].tl<=tl&&tr<=Q[idd[i]].tr) continue;
        if(Q[idd[i]].tl<=mid) swap(idd[i],idd[++tt]);
    }
    Divide_Conquer(ml,ml+ttl-1,tl,mid,tt);
    tt=0;
    for(int i=1;i<=tot;i++)
    {
        if(Q[idd[i]].tl<=tl&&tr<=Q[idd[i]].tr) continue;
        if(Q[idd[i]].tr>mid) swap(idd[i],idd[++tt]);
    }
    Divide_Conquer(ml+ttl,mr,mid+1,tr,tt);
}
int main()
{
    memset(ans,-1,sizeof ans);
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);insert(i,x);
    }
    for(int i=1,ot,x,y,l,r;i<=m;i++)
    {
        scanf("%d",&ot);
        if(ot==0) ++day,scanf("%d%d",&x,&y),O[++cntO]=opt(day,x,y);
        if(ot==1) scanf("%d%d%d%d",&l,&r,&x,&y),Q[++cntQ]=Query(l,r,x,max(0,day-y)+1,day,i),ans[i]=query(l-1,r,x),idd[cntQ]=cntQ;
    }
    sort(O+1,O+1+cntO);
    Divide_Conquer(1,cntO,1,day,cntQ);
    for(int i=1;i<=m;i++)
        if(ans[i]!=-1) printf("%d\n",ans[i]);
    #ifdef LOCAL
        system("pause");
    #endif
}