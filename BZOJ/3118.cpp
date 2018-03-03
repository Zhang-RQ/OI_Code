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
const int MAXN=310;
const int MAXM=5050;
const double eps=1E-8;
const double INF=1000000000;
struct NOde{
    int u,v,w,f,a,b;
}e[1010];
struct node{
    int nxt,v,no;
}Edge[MAXM];
int head[MAXN],cnt_e;
int n,m,st[MAXN<<1][10],lca[MAXN<<1][10],lg2[1010],cnt,pos[MAXN],fa_no[MAXN],fa[MAXN];
int cm=0;
double a[10010][1010];
inline void add(int u,int v,int no)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].no=no;
    head[u]=cnt_e;
}
void dfs(int x,int father,int dep)
{
    st[pos[x]=++cnt][0]=dep;
    lca[cnt][0]=x;
    fa[x]=father;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) {fa_no[x]=Edge[i].no;continue;}
        dfs(v,x,dep+1);
        st[++cnt][0]=dep;
        lca[cnt][0]=x;
    }
}
void init()
{
    for(int i=2;i<=cnt;i++) lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];j++)
        for(int i=1;i+(1<<j)-1<=cnt;i++)
            st[i][j]=st[i][j-1]<st[i+(1<<(j-1))][j-1]?st[i][j-1]:st[i+(1<<(j-1))][j-1],
            lca[i][j]=st[i][j-1]<st[i+(1<<(j-1))][j-1]?lca[i][j-1]:lca[i+(1<<(j-1))][j-1];
}
int get_lca(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
}
void deal(int x)
{
    int u=e[x].u,v=e[x].v,lc=get_lca(u,v),w=e[x].w;
    while(u!=lc) a[++cm][x]=-1,a[cm][fa_no[u]]=-1,a[cm][0]=w-e[fa_no[u]].w,u=fa[u];
    while(v!=lc) a[++cm][x]=-1,a[cm][fa_no[v]]=-1,a[cm][0]=w-e[fa_no[v]].w,v=fa[v];
}
namespace LP{
    int n,m;
    void Pivot(int l,int e)
    {
        double t=a[l][e];a[l][e]=1;
        for(int i=0;i<=n;i++) a[l][i]/=t;
        for(int i=0;i<=m;i++) if(i!=l&&fabs(a[i][e])>eps)
        {
            t=a[i][e];a[i][e]=0;
            for(int j=0;j<=n;j++)
                a[i][j]-=t*a[l][j];
        }
    }
    bool init()
    {
        int l=0,e=0;
        while(true)
        {
            l=e=0;
            for(int i=1;i<=m;i++) if(a[i][0]<-eps&&(!l||rand()&1)) l=i;
            if(!l) break;
            for(int i=1;i<=n;i++) if(a[l][i]<-eps&&(!e||rand()&1)) e=i;
            if(!e) {puts("Infeasible");return false;}
            Pivot(l,e);
        }
        return true;
    }
    bool Simplex()
    {
        int l=0,e=0;
        double mn=INF;
        while(true)
        {
            l=e=0;mn=INF;
            for(int i=1;i<=n;i++)
                if(a[0][i]>eps) {e=i;break;}
            if(!e) break;
            for(int i=1;i<=m;i++)
                if(a[i][e]>eps&&mn>a[i][0]/a[i][e])
                    mn=a[i][0]/a[i][e],l=i;
            if(!l) {puts("Unbounded");return false;}
            Pivot(l,e);
        }
        return true;
    }
}
int main()
{
    srand((ull) new char);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d%d%d",&e[i].u,&e[i].v,&e[i].w,&e[i].f,&e[i].a,&e[i].b);
        if(e[i].f) add(e[i].u,e[i].v,i),add(e[i].v,e[i].u,i),a[0][i]=-e[i].b;
        else a[0][i]=-e[i].a;
    }
    dfs(1,0,1);
    init();
    for(int i=1;i<=m;i++) if(!e[i].f) deal(i);
    LP::n=m;LP::m=cm;
    if(LP::init()&&LP::Simplex())
        printf("%.0lf\n",a[0][0]);

}
