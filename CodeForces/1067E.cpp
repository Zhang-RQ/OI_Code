#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXN=5E5+10;

template<typename T1,typename T2>
    void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
    void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
    T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
    T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n;
int f[2][MAXN],g[2][MAXN];
vector<int> T[MAXN];

void dfs(int x,int fa)
{
    g[0][x]=1;
    for(int v:T[x])
        if(v!=fa)
        {
            dfs(v,x);
            int f0=f[0][x],f1=f[1][x],g0=g[0][x],g1=g[1][x];
            f[0][x]=f[1][x]=g[0][x]=g[1][x]=0;
            //disconnect
            Inc(f[0][x],Add(1ll*f0*Add(g[0][v],g[1][v])%P,1ll*g0*Add(f[0][v],f[1][v])%P));
            Inc(f[1][x],Add(1ll*f1*Add(g[0][v],g[1][v])%P,1ll*g1*Add(f[0][v],f[1][v])%P));
            Inc(g[0][x],1ll*g0*Add(g[0][v],g[1][v])%P);
            Inc(g[1][x],1ll*g1*Add(g[0][v],g[1][v])%P);
            //connect
            Inc(f[0][x],Add(1ll*f0*g[1][v]%P,1ll*g0*f[1][v]%P));
            Inc(f[1][x],Add(1ll*f1*Add(g[0][v],g[1][v])%P,1ll*g1*Add(f[0][v],f[1][v])%P));
            Inc(f[1][x],Add(Add(1ll*f0*g[0][v]%P,1ll*g0*f[0][v]%P),1ll*g0*g[0][v]%P));
            Inc(g[0][x],1ll*g0*g[1][v]%P);
            Inc(g[1][x],1ll*g1*Add(g[0][v],g[1][v])%P);
            Inc(g[1][x],1ll*g0*g[0][v]%P);
        }
}

int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
        scanf("%d%d",&u,&v),
        T[u].push_back(v),
        T[v].push_back(u);
    dfs(1,0);
    printf("%lld\n",2ll*Add(f[0][1],f[1][1])%P);
}
