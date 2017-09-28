#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
#define MAXN 40010
using namespace std;
typedef long long ll;
struct node{
    int v,nxt,val;
}Edge[MAXN<<1];
int head[MAXN],cnte=0;
void add(int u,int v,int val)
{
    Edge[++cnte].v=v;
    Edge[cnte].val=val;
    Edge[cnte].nxt=head[u];
    head[u]=cnte;
}
int st[MAXN<<2][20],lca[MAXN<<2][20],dep[MAXN],pos[MAXN];
int lg2[MAXN<<2];
int cnt=0;
void dfs(int x,int depth,int fa)
{
    st[pos[x]=++cnt][0]=dep[x]=depth;
    lca[cnt][0]=x;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,depth+Edge[i].val,x);
        st[++cnt][0]=depth;
        lca[cnt][0]=x;
    }
}
int find_lca_dep(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    return min(st[x][len],st[y-(1<<len)+1][len]);
}
int main()
{
    int T;
    lg2[1]=0;
    for(int i=2;i<80020;i++)
        lg2[i]=lg2[i>>1]+1;
    scanf("%d",&T);
    while(T--)
    {
        int n,q,u,v,val;
        memset(head,0,sizeof(head));
        cnte=0;
        cnt=0;
        scanf("%d%d",&n,&q);
        for(int i=1;i<n;i++)
            scanf("%d%d%d",&u,&v,&val),add(u,v,val),add(v,u,val);
        dfs(1,0,0);
        for(int j=1;j<=lg2[cnt];j++)
            for(int i=1;i+(1<<j)-1<=cnt;i++)
            {
                if(st[i][j-1]<=st[i+(1<<(j-1))][j-1])
                {
                    st[i][j]=st[i][j-1];
                    lca[i][j]=lca[i][j-1];
                }else{
                    st[i][j]=st[i+(1<<(j-1))][j-1];
                    lca[i][j]=lca[i+(1<<(j-1))][j-1];
                }
            }
        for(int i=1;i<=q;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",dep[x]+dep[y]-2*find_lca_dep(x,y));
        }
    }
}
