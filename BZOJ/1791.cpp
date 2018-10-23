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

const int MAXN=1E6+233;
const int MAXM=1E6+233;

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
    int v,w,nxt;
}Edge[MAXM<<1];

bool vis[MAXN],inR[MAXN];
int n,head[MAXN],cnt_e=1,stk[MAXN],top,Rt[MAXN<<1],Rtsiz;
ll f[MAXN],Ans,tAns,Fad[MAXN];
deque<int> q;
deque<ll> qs;

void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].w=w;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

void Find_Ring(int x,int fa,int eid)
{
    if(Rtsiz) return;
    stk[++top]=x;
    vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        Fad[x]=Edge[i].w;
        int v=Edge[i].v;
        if(eid==(i^1)) continue;
        else if(vis[v])
        {
            while(stk[top]!=v)
                inR[stk[top]]=1,Rt[++Rtsiz]=(stk[top--]);
            Rt[++Rtsiz]=(v);inR[v]=1;
            return;
        }
        Find_Ring(v,x,i);
        if(Rtsiz) return;
    }
    --top;
}

void dfs(int x,int fa)
{
    ll mx=0;vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||inR[v]) continue;
        dfs(v,x);
        f[x]=max(f[x],Edge[i].w+f[v]);
        tAns=max(tAns,mx+f[v]+Edge[i].w);
        mx=max(mx,f[v]+Edge[i].w);
    }
}

int main()
{
    read(n);
    for(int u=1,v,w;u<=n;u++)
    {
        read(v);read(w);
        add(u,v,w);add(v,u,w);
    }
    for(int x=1;x<=n;x++)
    {
        if(vis[x]) continue;
        Rtsiz=0;tAns=0;top=0;q.clear();qs.clear();
        Find_Ring(x,0,0);
        if(!Rtsiz) dfs(x,0);
        else
        {
            for(int i=1;i<=Rtsiz;i++)
                dfs(Rt[i],0);
            int sz=Rtsiz;
            for(int i=1;i<=sz;i++)
                Rt[++Rtsiz]=(Rt[i]);
            q.push_back(0);qs.push_back(0);
            ll Sum=0;
            for(int i=2;i<=Rtsiz;i++)
            {
                Sum+=Fad[Rt[i]];
                while(q.size()&&i-q.front()>sz-1) q.pop_front(),qs.pop_front();
                if(q.size())tAns=max(f[Rt[i]]+Sum+f[Rt[q.front()]]-qs.front(),tAns);
                while(q.size()&&f[Rt[i]]-Sum>=f[Rt[q.back()]]-qs.back()) q.pop_back(),qs.pop_back();
                q.push_back(i);qs.push_back(Sum);
            }
        }
        Ans+=tAns;
    }
    printf("%lld\n",Ans);
}