#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E6+10;
const int MAXP=8E6+10;

bool vis[MAXN];
ull n,pos[MAXN],g[MAXN],lim;
int id[MAXP],pr[MAXN],pc,cnt,npc;

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

int ID(ull x){return id[x<=lim?x:(MAXP-n/x)];}

ull S(int t,int j)
{
    ull ret=g[t]-3*j+3,v=pos[t];
    if(j>npc) return ret;
    for(int k=j;k<=npc&&1llu*pr[k]*pr[k]<=v;k++)
    {
        ull pw=pr[k];
        for(int e=1;pw*pr[k]<=v;pw*=pr[k],e++)
            ret+=(2*e+1)*S(ID(v/pw),k+1)+2*e+3;
    }
    return ret;
}

void solve()
{
    scanf("%llu",&n);cnt=0;
    lim=sqrt(n);npc=upper_bound(pr+1,pr+1+pc,lim)-pr-1;
    for(ull i=1,nxt;i<=n;i=nxt+1)
        pos[++cnt]=n/i,nxt=n/(n/i);
    for(int i=1;i<=cnt;i++)
        g[i]=pos[i]-1,id[pos[i]<=lim?pos[i]:(MAXP-n/pos[i])]=i;
    for(int j=1;j<=npc;j++)
        for(int i=1;i<=cnt;i++)
        {
            if(1llu*pr[j]*pr[j]>pos[i]) break;
            g[i]-=g[ID(pos[i]/pr[j])]-j+1;
        }
    for(int i=1;i<=cnt;i++) g[i]*=3;
    printf("%llu\n",S(1,1)+1);
}

int main()
{
    int T;
    for(scanf("%d",&T),sieve();T--;solve());
}