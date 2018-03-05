// MLE???
#include<cstdio>
#include<queue>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1E5+5;
const int MAXM=2E5+5;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
struct PQ{
    priority_queue<int> _heap,_del;
    inline void push(int x)  {_heap.push(x);}
    inline void del(int x) {_del.push(x);}
    inline int size()  {return _heap.size()-_del.size();}
    inline void pop()
    {
        while(_del.size()&&_heap.top()==_del.top())
            _heap.pop(),_del.pop();
        if(_heap.size()) _heap.pop();
    }
    inline int top()
    {
        while(_del.size()&&_heap.top()==_del.top())
            _heap.pop(),_del.pop();
        if(_heap.size()) return _heap.top();
        return -1;
    }
    inline int sec()
    {
        if(size()<2) return -1;
        int tmp=top();pop();
        int ret=top();
        _heap.push(tmp);
        return ret;
    }
}h1[MAXN],h2[MAXN],ans;
void insert(int x) {if(h2[x].size()>1) ans.push(h2[x].top()+h2[x].sec());}
void erase(int x) {if(h2[x].size()>1) ans.del(h2[x].top()+h2[x].sec());}
int siz[MAXN],mx_rt,rt,fa[MAXN];
int dep[MAXN],st[MAXN<<1][20],lg2[MAXN<<1],cnt,pos[MAXN];
bool status[MAXN];
bool vis[MAXN];
void get_root(int x,int fa,int sz)
{
    int mx=siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        get_root(v,x,sz);
        mx=max(mx,siz[v]);
        siz[x]+=siz[v];
    }
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) mx_rt=mx,rt=x;
}
void dfs(int x,int fa,int dis,int _rt)
{
    h1[_rt].push(dis);
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            dfs(Edge[i].v,x,dis+1,_rt);
}
void solve(int x)
{
    vis[x]=1;h2[x].push(0);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mx_rt=MAXN+10;
        get_root(v,0,siz[x]>siz[v]?siz[v]:siz[v]-siz[x]);
        dfs(v,0,1,rt);
        //printf("rt=%d top=%d\n",rt,h1[rt].top());
        fa[rt]=x;h2[x].push(h1[rt].top());
        solve(rt);
    }
    //printf("%d %d %d\n",x,h2[x].top(),h2[x].sec());
    insert(x);
}
void dfsi(int x,int fa)
{
    st[pos[x]=++cnt][0]=dep[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dep[v]=dep[x]+1;
        dfsi(v,x);
        st[++cnt][0]=dep[x];
    }
}
void init()
{
    for(int i=2;i<=cnt;i++) lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];j++)
        for(int i=1;i+(1<<j)-1<=cnt;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int Dis(int x,int y)
{
    int px=pos[x],py=pos[y];
    if(px>py) swap(px,py);
    int len=lg2[py-px+1];
    return dep[x]+dep[y]-2*min(st[px][len],st[py-(1<<len)+1][len]);
}
void LightOn(int x)
{
    status[x]=1;
    erase(x);h2[x].del(0);insert(x);
    for(int i=x;fa[i];i=fa[i])
    {
        erase(fa[i]);
        if(h1[i].size()) h2[fa[i]].del(h1[i].top());
        h1[i].del(Dis(fa[i],x));
        if(h1[i].size()) h2[fa[i]].push(h1[i].top());
        insert(fa[i]);
    }
}
void LightOff(int x)
{
    status[x]=0;
    erase(x);h2[x].push(0);insert(x);
    for(int i=x;fa[i];i=fa[i])
    {
        erase(fa[i]);
        if(h1[i].size()) h2[fa[i]].del(h1[i].top());
        h1[i].push(Dis(fa[i],x));
        if(h1[i].size()) h2[fa[i]].push(h1[i].top());
        insert(fa[i]);
    }
}
int n,u,v,q,x,ct;
char opt[10];
int main()
{
    scanf("%d",&n);
    ct=n;
    for(int i=1;i<n;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfsi(1,0);init();
    mx_rt=MAXN+10;
    get_root(1,0,n);
    solve(rt);
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%s",opt+1);
        if(opt[1]=='G') printf(ct?"%d\n":"-1\n",ans.top());
        else
        {
            scanf("%d",&x);
            if(status[x]) LightOff(x),++ct;
            else LightOn(x),--ct;
        }
    }
}
