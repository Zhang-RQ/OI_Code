#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=8E5+10;
const int MAXP=MAXN*8;

bool vis[MAXN];
int pr[MAXN],pc,id[MAXP],cnt,lim,npc;
ll pos[MAXP],g[MAXN],n;

void sieve()
{
    for(int i=2;i<MAXN;i++)
    {
        if(!vis[i]) pr[++pc]=i;
        for(int j=1;j<=pc&&i*pr[j]<MAXN;j++)
        {
            vis[i*pr[j]]=1;
            if(!(i%pr[j])) break;
        }
    }
}

int ID(ll x){return id[x<=lim?x:(MAXP-n/x)];}

ll S(int t,int j)
{
    ll ret=g[t]-j*4+4,v=pos[t];
    if(j>npc) return ret;
    for(int k=j;k<=npc&&1ll*pr[k]*pr[k]<=v;k++)
    {
        ll pw=pr[k];
        for(int e=1;pw*pr[k]<=v;e++,pw*=pr[k])
            ret+=(3*e+1)*S(ID(v/pw),k+1)+3*e+4;
    }
    return ret;
}

void solve()
{
    scanf("%lld",&n);cnt=0;lim=sqrt(n);
    npc=upper_bound(pr+1,pr+1+pc,lim)-pr-1;
    for(ll i=1,nxt;i<=n;i=nxt+1)
        pos[++cnt]=n/i,nxt=n/(n/i);
    for(int i=1;i<=cnt;i++)
        g[i]=pos[i]-1,id[pos[i]<=lim?pos[i]:(MAXP-n/pos[i])]=i;
    for(int j=1;j<=npc;j++)
        for(int i=1;i<=cnt;i++)
        {
            if(1ll*pr[j]*pr[j]>pos[i]) break;
            g[i]-=g[ID(pos[i]/pr[j])]-j+1;
        }
    for(int i=1;i<=cnt;i++) g[i]*=4;
    printf("%lld\n",S(1,1)+1);
}

int main()
{
    int T;
    for(scanf("%d",&T),sieve();T--;solve());
}