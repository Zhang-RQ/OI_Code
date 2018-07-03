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

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int MAXN=100010;
const int MAXM=500010<<1;
const uint base=100003;

struct node{
    int v,nxt;
}Edge[MAXM];

int cnt,n,m,head[MAXN],cnt_e,rk[MAXN],rrk[MAXN],val[MAXN],rt[MAXN];
uint pw[MAXN];
bool vis[MAXN];

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

namespace President_tree{
    struct node{
        int l,r;
        uint hsh;
    }t[MAXN<<6];
    void insert(int &x,int l,int r,int pos)
    {
        t[++cnt]=t[x];x=cnt;
        if(l==r) return t[x].hsh++,void();
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].l,l,mid,pos);
        else insert(t[x].r,mid+1,r,pos);
        t[x].hsh=t[t[x].l].hsh*pw[r-mid]+t[t[x].r].hsh;
    }
    inline bool cmp(int x,int y)
    {
        if(t[x].hsh==t[y].hsh) return 0;
        int L=1,R=n;
        while(L<R)
        {
            int mid=(L+R)>>1;
            if(t[t[x].l].hsh!=t[t[y].l].hsh) x=t[x].l,y=t[y].l,R=mid;
            else x=t[x].r,y=t[y].r,L=mid+1;
        }
        return t[x].hsh<t[y].hsh;
    }
    void dfs(int x,int l,int r)
    {
        if(!x) return;
        if(l==r)
        {
            for(int i=1;i<=t[x].hsh;i++) printf("%d ",rrk[l]);
            return;
        }
        int mid=(l+r)>>1;
        dfs(t[x].l,l,mid);
        dfs(t[x].r,mid+1,r);
    }
}

struct Pnt{
    int x,rt;
    Pnt(){}
    Pnt(int _x,int _rt){x=_x;rt=_rt;}
    bool operator < (const Pnt &rhs) const {return !President_tree::cmp(rt,rhs.rt);}
};


inline char nc(){
  static char buf[100000],*p1=buf,*p2=buf;
  return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}

inline void read(int &x){
  char c=nc(); x=0;
  for(;c>'9'||c<'0';c=nc());
  for(;c>='0'&&c<='9';x=x*10+c-'0',c=nc());
}

priority_queue<Pnt> pq;

int main()
{   
    pw[0]=1;
    read(n),read(m);
    for(int i=1;i<=n;i++) read(rrk[i]),rk[rrk[i]]=i;
    for(int i=1;i<=n;i++) read(val[i]),val[i]=rk[val[i]];
    for(int i=1,u,v;i<=m;i++)
        read(u),read(v),add(u,v),add(v,u);
    for(int i=1;i<=n;i++)
        pw[i]=pw[i-1]*base;
    pq.push(Pnt(1,0));
    while(!pq.empty())
    {
        Pnt t=pq.top();pq.pop();
        if(vis[t.x]) continue;
        int cur=rt[t.x];vis[t.x]=1;
        President_tree::insert(cur,1,n,val[t.x]);
        for(int i=head[t.x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(!rt[v]||President_tree::cmp(cur,rt[v]))
                rt[v]=cur,pq.push(Pnt(v,cur));
        }
    }
    President_tree::insert(rt[n],1,n,val[n]);
    President_tree::dfs(rt[n],1,n);
    puts("");
}