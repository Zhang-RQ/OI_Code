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
const int MAXN=1E5+5;
const int MAXM=2E5+5;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,ans[MAXN],arr[MAXN],val[MAXN];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
struct NODE{
    int ls,rs,val;
}t[MAXN<<6];
int cnt=0,n,u,rt[MAXN],ccnt;
void insert(int &x,int l,int r,int pos)
{
    if(!x) x=++cnt;
    t[x].val++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) insert(t[x].ls,l,mid,pos);
    else insert(t[x].rs,mid+1,r,pos);
}
int query(int x,int l,int r,int ql,int qr)
{
    if(!x) return 0;
    if(ql<=l&&r<=qr) return t[x].val;
    int mid=(l+r)>>1,ret=0;
    if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,qr);
    if(qr>mid)  ret+=query(t[x].rs,mid+1,r,ql,qr);
    return ret;
}
int merge(int x,int y)
{
    if(!x||!y) return x+y;
    int nt=++cnt;
    t[nt].val=t[x].val+t[y].val;
    t[nt].ls=merge(t[x].ls,t[y].ls);
    t[nt].rs=merge(t[x].rs,t[y].rs);
    return nt;
}
void dfs(int x,int fa)
{
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x);
        rt[x]=merge(rt[x],rt[v]);
    }
    ans[x]=query(rt[x],1,ccnt,val[x]+1,ccnt);
    insert(rt[x],1,ccnt,val[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]),arr[i]=val[i];
    sort(arr+1,arr+1+n);
    ccnt=unique(arr+1,arr+1+n)-arr-1;
    for(int i=1;i<=n;i++) val[i]=lower_bound(arr+1,arr+1+ccnt,val[i])-arr;
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&u);
        add(u,i);add(i,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
}
