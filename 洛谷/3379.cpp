%:pragma GCC optimize(2)
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

#define M 500100
#define N 500100
int n,m,root,u,v,cnt=0;
int head[M],pos[M];
int lg2[M<<1];
int st[M<<1][21],lca[M<<1][21];
struct Node{
    int v,nxt;
}Edge[N<<1];
int cnte=0;
inline int read()
{
    static int f,ret;
    static char c;
    ret=0,f=1;
    c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
    return f==1?ret:-ret;
}

inline void add(int &u,int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
void dfs(int x,int fa,int depth)
{
    st[pos[x]=++cnt][0]=depth;
    lca[cnt][0]=x;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x,depth+1);
        st[++cnt][0]=depth;
        lca[cnt][0]=x;
    }
}
inline void work()
{
    for(int i=2;i<=cnt;++i)  lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];++j)
    {
        for(int i=1;i+(1<<j)-1<=cnt;++i)
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
    }
}
inline int get_lca_id(int x,int y)
{
    if(x>y) swap(x,y);
    int len=lg2[y-x+1],le=1<<len;
    if(st[x][len]<=st[y-le+1][len]) return lca[x][len];
    else return lca[y-le+1][len];
}
int main()
{
    scanf("%d%d%d",&n,&m,&root);
    for(int i=1;i<n;++i)
    {
        u=read();v=read();
        add(u,v);
        add(v,u);
    }
    dfs(root,0,0);
    work();
    for(int i=1;i<=m;++i)
    {
        u=read();v=read();
        printf("%d\n",get_lca_id(pos[u],pos[v]));
    }
}
