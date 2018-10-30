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

const int MAXN=5E5+10;
const int MAXM=5E5+10;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
            x=0;static char ch=get_char();
            while(!isdigit(ch)) ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
        }
}

using namespace FastIO;

struct __edge{
	int v,nxt;
}Edge[MAXM<<1];

vector<int> nd;
int head[MAXN],cnt_e,cnt,Ring_Siz[MAXN],num[MAXN];
int n,q,Rt[MAXN],CC[MAXN],stk[MAXN],top,jmp[MAXN][20],dep[MAXN];
bool ins[MAXN],vis[MAXN],inR[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void Find_Ring(int x)
{
    if(nd.size()) return;
    stk[++top]=x;ins[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!ins[v]) Find_Ring(v);
        else
        {
            while(stk[top]!=v) inR[stk[top]]=1,nd.push_back(stk[top--]);
            nd.push_back(v);--top;
        }
        if(nd.size()) return;
    }
    if(nd.size()) return;
    --top;ins[x]=0;
}

void dfs(int x,int fa,int rt)
{
    dep[x]=dep[fa]+1;
    Rt[x]=rt;CC[x]=CC[rt];
    jmp[x][0]=fa;vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!inR[Edge[i].v])
            dfs(Edge[i].v,x,rt);
}

int LCA(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int j=19;~j;j--)
        if(dep[jmp[x][j]]>=dep[y])
            x=jmp[x][j];
    if(x==y) return x;
    for(int j=19;~j;j--)
        if(jmp[x][j]!=jmp[y][j])
            x=jmp[x][j],y=jmp[y][j];
    return jmp[x][0];
}

int main()
{
    read(n);read(q);
    for(int i=1,a;i<=n;i++)
    {
        read(a);
        if(a!=i) add(a,i);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])
        {
            nd.clear();
            Find_Ring(i);
            if(!nd.size())
                CC[i]=++cnt,dfs(i,0,i);
            else
            {
                ++cnt;
                for(int j=0;j<(signed)nd.size();j++)
                    CC[nd[j]]=cnt,dfs(nd[j],0,nd[j]),Ring_Siz[nd[j]]=nd.size(),num[nd[j]]=j+1;
            }
        }
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    for(int i=1,a,b;i<=q;i++)
    {
        read(a);read(b);
        if(CC[a]!=CC[b]) puts("-1 -1");
        else
        {
            if(Rt[a]==Rt[b])
            {
                int lca=LCA(a,b);
                printf("%d %d\n",dep[a]-dep[lca],dep[b]-dep[lca]);
            }
            else
            {
                if(num[Rt[a]]<num[Rt[b]])
                {
                    int dlt=num[Rt[b]]-num[Rt[a]];
                    int x1=dep[a]+dlt-1,y1=dep[b]-1,x2=dep[a]-1,y2=dep[b]+Ring_Siz[Rt[a]]-(dlt)-1;
                    if(max(x1,y1)<max(x2,y2)) printf("%d %d\n",x1,y1);
                    else if(max(x1,y1)>max(x2,y2)) printf("%d %d\n",x2,y2);
                    else if(min(x1,y1)<min(x2,y2)) printf("%d %d\n",x1,y1);
                    else if(min(x1,y1)>min(x2,y2)) printf("%d %d\n",x2,y2);
                    else if(x1>=y1) printf("%d %d\n",x1,y1);
                    else printf("%d %d\n",x2,y2);
                }
                else
                {
                    int dlt=num[Rt[a]]-num[Rt[b]];
                    int x1=dep[a]+Ring_Siz[Rt[a]]-dlt-1,y1=dep[b]-1,x2=dep[a]-1,y2=dep[b]+dlt-1;
                    if(max(x1,y1)<max(x2,y2)) printf("%d %d\n",x1,y1);
                    else if(max(x1,y1)>max(x2,y2)) printf("%d %d\n",x2,y2);
                    else if(min(x1,y1)<min(x2,y2)) printf("%d %d\n",x1,y1);
                    else if(min(x1,y1)>min(x2,y2)) printf("%d %d\n",x2,y2);
                    else if(x1>=y1) printf("%d %d\n",x1,y1);
                    else printf("%d %d\n",x2,y2);
                }
            }
        }
    }
}