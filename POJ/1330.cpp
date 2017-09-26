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
using namespace std;
typedef long long ll;

#define M 10100
#define N 20100
int head[M];
struct Node{
    int val,nxt,v;
}Edge[N];
int cnte=0;
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}

int st[N<<1][20],lca[N<<1][20],dep[N],pos[N],cnt=0,lg2[N<<1];
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
int get_lca_id(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    if(st[x][len]<=st[y-(1<<len)+1][len])   return lca[x][len];
    else return lca[y-(1<<len)+1][len];
}
int get_lca_val(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    return min(st[x][len],st[y-(1<<len)+1][len]);
}
bool in[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(in,0,sizeof(in));
        memset(head,0,sizeof(head));
        cnt=0;
        cnte=0;
        int n,a,b;
        scanf("%d",&n);
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&a,&b);
            add(a,b,1);
            add(b,a,1);
            in[b]=1;
        }
        int root=1;
        for(int i=1;i<=n;i++) if(!in[i]) root=i;
        dfs(root,0,0);
        lg2[1]=0;
        for(int i=2;i<=cnt;i++)   lg2[i]=lg2[i>>1]+1;
        for(int j=1;j<=lg2[cnt];j++)
            for(int i=1;i+(1<<j)-1<=cnt;i++)
            {
                if(st[i][j-1]<=st[i+(1<<(j-1))][j-1])
                {
                    st[i][j]=st[i][j-1];
                    lca[i][j]=lca[i][j-1];
                }
                else
                {
                    st[i][j]=st[i+(1<<(j-1))][j-1];
                    lca[i][j]=lca[i+(1<<(j-1))][j-1];
                }
            }
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",get_lca_id(x,y));
    }
}
