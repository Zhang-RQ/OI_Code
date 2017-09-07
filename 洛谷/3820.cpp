#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
bool vis[1000100];
int s[1000100],fa[1000100],f[1000100],x,y;//s表示连通块面积，f表示所在联通块的编号
int mp[1000100];
int N,M;
int c=0;
inline int getid(int x,int y)
{
    return (x-1)*M+y;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs(int x,int y)
{
    int id=getid(x,y);
    if(vis[id]||(!mp[id]))   return;
    f[id]=c;
    vis[id]=true;
    ++s[c];
    if(x<N) dfs(x+1,y);
    if(x>1) dfs(x-1,y);
    if(y<M) dfs(x,y+1);
    if(y>1) dfs(x,y-1);
    return;
}
void merge(int x,int y,int x1,int y1)
{
    int id=find(f[getid(x,y)]),id1=find(f[getid(x1,y1)]);
    if(id==id1||!mp[getid(x,y)]||!mp[getid(x1,y1)]) return;
        s[id]+=s[id1];
        s[id1]=0;
        fa[id1]=id;
        return;

}
int main()
{
    scanf("%d%d",&N,&M);
    char tmp,ttt;
    scanf("%c",&ttt);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            scanf("%c",&tmp);
            if(tmp=='.') mp[getid(i,j)]=1;
            if(tmp=='*') mp[getid(i,j)]=0;
        }
        scanf("%c",&ttt);
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(mp[getid(i,j)]&&(!vis[getid(i,j)]))
            {
                ++c;
                dfs(i,j);
            }
        }
    }
    for(int i=1;i<=c;i++) fa[i]=i;
    int Q;
    int opt;
    int w;
    scanf("%d",&Q);
    while(Q--)
    {
        int pans=0;
        int ans=0;
        scanf("%d",&opt);
        scanf("%d",&w);
        if(opt==1)
        {
            for(int i=1;i<=w;i++)
            {
                scanf("%d%d",&x,&y);
                    if(mp[getid(x,y)]) if(ans<s[find(f[getid(x,y)])])
                    {
                        ans=s[find(f[getid(x,y)])];
                        pans=i;
                    }
            }
            printf("%d\n",pans);
        }else{
            for(int i=1;i<=w;i++)
                {
                    if(mp[getid(x,y)])
                        --s[find(f[getid(x,y)])],mp[getid(x,y)]=0,f[getid(x,y)]=0;
                        else
                        {
                            mp[getid(x,y)]=1;
                            c++;
                            f[getid(x,y)]=c;
                            fa[c]=c;
                            s[c]++;
                            if (x>1)   merge(x,y,x-1,y);
                            if (y>1)   merge(x,y,x,y-1);
                            if (x<N)   merge(x,y,x+1,y);
                            if (y<M)   merge(x,y,x,y+1);
                        }
                }
                }
    }
}
