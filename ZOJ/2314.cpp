#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=500;
const int MAXM=1E6+10;

struct edge_t{
    int v,nxt;
    ll f;
}Edge[MAXM];

int n,m,cnt_e=1,head[MAXN],S=0,T=MAXN-1,lvl[MAXN],F[MAXN],RF[MAXM],L[MAXM];
queue<int> q;

void _add(int u,int v,ll f)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].f=f;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

void add(int u,int v,ll f,ll f2=0){_add(u,v,f);_add(v,u,f2);}

bool BFS()
{
    memset(lvl,0,sizeof lvl);
    q.push(S);lvl[S]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].f) continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[T]!=0;
}

ll dfs(int x,ll cur)
{
    if(x==T) return cur;
    ll adf=0;
    for(int i=head[x];i&&adf<cur;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!Edge[i].f||lvl[v]!=lvl[x]+1) continue;
        ll mnf=dfs(v,min(cur-adf,Edge[i].f));
        if(!mnf) lvl[v]=0;
        Edge[i].f-=mnf;Edge[i^1].f+=mnf;
        adf+=mnf;
    }
    return adf;
}

void solve()
{
    memset(head,0,sizeof head);cnt_e=1;
    memset(F,0,sizeof F);
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,l,r;i<=m;i++)
    {
        scanf("%d%d%d%d",&u,&v,&l,&r);
        add(u,v,r-l);RF[i]=r-l;L[i]=l;
        F[v]+=l;F[u]-=l;
    }
    ll Ans=0;
    for(int i=1;i<=n;i++)
    {
        if(F[i]>0) add(S,i,F[i]),Ans-=F[i];
        else if(F[i]<0) add(i,T,-F[i]);
    }
    while(BFS()) Ans+=dfs(S,1ll<<60);
    if(Ans<0) puts("NO");
    else
    {
        puts("YES");
        for(int i=1;i<=m;i++) printf("%lld\n",RF[i]-Edge[2*i].f+L[i]);
    }
    puts("");
}

int main()
{
    int T;
    for(scanf("%d",&T);T--;solve());
}