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

const int P=45989;
const int MAXN=1E2+5;
const int MAXM=2E2+5;

struct __edge{
    int nxt,v;
}Edge[MAXM];

int head[MAXN],cnt_e=1;

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

int n,m,s,t,T;

struct Matrix{
    ll val[125][125];
    ll* operator [] (const int &i) {return val[i];}
    const ll * operator [] (const int &i) const {return val[i];}
    Matrix operator *(const Matrix &a) const
    {
        Matrix ret;
        memset(ret.val,0,sizeof(ret.val));
        for(int i=0;i<=cnt_e;i++)
            for(int j=0;j<=cnt_e;j++)
                for(int k=0;k<=cnt_e;k++)
                    (ret.val[i][j]+=val[i][k]*a[k][j])%=P;
        return ret;
    }
    inline void print()
    {
        for(int i=0;i<=cnt_e;i++)
            for(int j=0;j<=cnt_e;j++)
                printf("%lld%c",val[i][j],j==cnt_e?'\n':' ');
        puts("");
    }
}A,B;

Matrix ksm(Matrix a,int b)
{
    Matrix ret,base=a;
    memset(ret.val,0,sizeof(ret.val));
    for(int i=0;i<=cnt_e;i++) ret.val[i][i]=1;
    while(b)
    {
        if(b&1) ret=base*ret;
        base=base*base;
        b>>=1;
    }
    return ret;
}

int main()
{
    scanf("%d%d%d%d%d",&n,&m,&T,&s,&t);
    for(int i=1,u,v;i<=m;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    for(int i=2;i<=cnt_e;i++)
    {
        for(int j=head[Edge[i].v];j;j=Edge[j].nxt)
            if(i!=(j^1)) A[i][j]++;
    }
    A=ksm(A,T-1);
    for(int i=head[s];i;i=Edge[i].nxt)
        B[0][i]++;
    B=B*A;
    ll ans=0;
    for(int i=2;i<=cnt_e;i++)
        if(Edge[i].v==t) (ans+=B[0][i])%=P;
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}