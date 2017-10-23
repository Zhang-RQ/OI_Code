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
typedef unsigned long long ull;
int mp[510][510];
bool vis[510][510];
int n,m;
int f[510];
struct node{
    int x,y;
    node(){}
    node(int a,int b):x(a),y(b){}
};
struct NODE{
    int l,r;
    int exist;
    friend bool operator <(NODE a,NODE b)
    {
        if(a.exist!=b.exist) return a.exist>b.exist;
        else if(a.r!=b.r) return a.r<b.r;
        else return a.l<b.l;
    }
}section[510];
queue<node> q;
inline bool inside(const int &x,const int &y)
{
    return 1<=x&&x<=n&&1<=y&&y<=m;
}
int bfs()
{
    int cnt=0;
    while (q.size())
    {
        int x=q.front().x;
        int y=q.front().y;
        q.pop();
        if(inside(x-1,y)&&mp[x][y]>mp[x-1][y]&&!vis[x-1][y])
            vis[x-1][y]=1,q.push(node(x-1,y));
        if(inside(x+1,y)&&mp[x][y]>mp[x+1][y]&&!vis[x+1][y])
            vis[x+1][y]=1,q.push(node(x+1,y));
        if(inside(x,y-1)&&mp[x][y]>mp[x][y-1]&&!vis[x][y-1])
            vis[x][y-1]=1,q.push(node(x,y-1));
        if(inside(x,y+1)&&mp[x][y]>mp[x][y+1]&&!vis[x][y+1])
            vis[x][y+1]=1,q.push(node(x,y+1));
    }
    for(int i=1;i<=m;i++)
        if(vis[n][i]) cnt++;
    return cnt;
}
void bfs_2(int s)
{
    memset(vis,0,sizeof(vis));
    queue<node> Q;
    Q.push(node(1,s));
    vis[1][s]=1;
    while(Q.size())
    {
        int x=Q.front().x;
        int y=Q.front().y;
        Q.pop();
        if(inside(x-1,y)&&mp[x][y]>mp[x-1][y]&&!vis[x-1][y])
            vis[x-1][y]=1,Q.push(node(x-1,y));
        if(inside(x+1,y)&&mp[x][y]>mp[x+1][y]&&!vis[x+1][y])
            vis[x+1][y]=1,Q.push(node(x+1,y));
        if(inside(x,y-1)&&mp[x][y]>mp[x][y-1]&&!vis[x][y-1])
            vis[x][y-1]=1,Q.push(node(x,y-1));
        if(inside(x,y+1)&&mp[x][y]>mp[x][y+1]&&!vis[x][y+1])
            vis[x][y+1]=1,Q.push(node(x,y+1));
    }
    for(int i=1;i<=m;i++)
    {
        if(!section[s].l&&vis[n][i]) section[s].l=i,section[s].exist=10;
        if(vis[n][i]) section[s].r=i;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=m;i++) q.push(node(1,i)),vis[1][i]=1;
    int tmp=bfs();
    if(tmp!=m) {printf("0\n%d\n",m-tmp);return 0;}
    for(int i=1;i<=m;i++) bfs_2(i);
    sort(section+1,section+1+m);
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=m;i++)
    {
        if(!section[i].exist) break;
        for(int j=section[i].l;j<=section[i].r;j++)
            f[j]=min(f[j],f[section[i].l-1]+1);
    }
    printf("1\n%d\n",f[m]);
}
