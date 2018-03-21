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
const double eps=1e-9;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,du[MAXN];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    du[u]++;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
double A[MAXN],B[MAXN],C[MAXN],e[MAXN],k[MAXN];
bool dfs(int x,int fa)
{
    double tmp=0;
    A[x]=k[x];
    B[x]=(1-k[x]-e[x])/du[x];
    C[x]=1-k[x]-e[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        if(!dfs(v,x)) return false;
        A[x]+=(1-k[x]-e[x])/du[x]*A[v];
        C[x]+=(1-k[x]-e[x])/du[x]*C[v];
        tmp+=(1-k[x]-e[x])/du[x]*B[v];
    }
    if(fabs(1-tmp)<eps) return true;
    A[x]/=(1-tmp);
    B[x]/=(1-tmp);
    C[x]/=(1-tmp);
    return true;
}
int T,n,u,v,t1,t2,Cs;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(A,0,sizeof A);memset(B,0,sizeof B);
        memset(C,0,sizeof C);memset(head,0,sizeof head);
        memset(du,0,sizeof du);
        cnt_e=0;
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            add(u,v);add(v,u);
        }
        for(int i=1;i<=n;i++)
            scanf("%d%d",&t1,&t2),k[i]=t1/100.0,e[i]=t2/100.0;
        printf("Case %d: ",++Cs);
        if(dfs(1,0)&&fabs(1-A[1])>eps)
        {
            printf("%.10lf\n",C[1]/(1-A[1]));
        }
        else puts("impossible");
    }
}
