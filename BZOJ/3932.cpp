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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=4000010;
struct node{
    int ls,rs,siz;
    ll sum;
}t[MAXN];
struct NODE{int t,v,f;}Q[200010];
bool operator < (NODE a,NODE b){return a.t<b.t;}
int cnt,val[100010],n,m,tot,s,e,p,rt[100010],x,a,b,c;
ll lstans=1;
void insert(int &x,int l,int r,int _x,int vl,int f)
{
    t[x=++cnt]=t[_x];
    t[x].siz+=f;t[x].sum+=val[vl]*f;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(vl<=mid) insert(t[x].ls,l,mid,t[_x].ls,vl,f);
    else insert(t[x].rs,mid+1,r,t[_x].rs,vl,f);
}
ll query(int x,int k,int l,int r)
{
    if(t[x].siz==k) return t[x].sum;
    if(l==r) return t[x].sum/t[x].siz*k;
    int lsiz=t[t[x].ls].siz;
    int mid=(l+r)>>1;
    if(lsiz>k) return query(t[x].ls,k,l,mid);
    else return t[t[x].ls].sum+query(t[x].rs,k-lsiz,mid+1,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&s,&e,&p);val[i]=p;
        Q[++tot].t=s;Q[tot].v=p;Q[tot].f=1;
        Q[++tot].t=e+1;Q[tot].v=p;Q[tot].f=-1;
    }
    sort(val+1,val+1+n);sort(Q+1,Q+1+tot);
    for(int i=1;i<=tot;i++) Q[i].v=lower_bound(val+1,val+1+n,Q[i].v)-val;
    for(int i=1,j=1;i<=n;i++)
    {
        rt[i]=rt[i-1];
        while(j<=tot&&Q[j].t==i) insert(rt[i],1,n,rt[i],Q[j].v,Q[j].f),j++;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x,&a,&b,&c);
        int k=1+(lstans*a+b)%c;
        if(k<t[rt[x]].siz) printf("%lld\n",lstans=query(rt[x],k,1,n));
        else printf("%lld\n",lstans=t[rt[x]].sum);
    }
}
