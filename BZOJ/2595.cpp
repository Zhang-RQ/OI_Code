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

const int MAXN=11;
const int mv[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

inline int id1(int x,int y){return 10*x+y;}
inline int id2(int x,int y,int s) {return x*100000+y*10000+s;}
inline void rid1(int S,int &x,int &y) {x=S/10;y=S%10;}
inline void rid2(int S,int &x,int &y,int &s) {x=S/100000;y=(S%100000)/10000;s=S%10000;}

int f[MAXN][MAXN][1<<10],frm[MAXN][MAXN][1<<10],n,m,val[MAXN][MAXN],tot;
bool vis[MAXN][MAXN],inq[MAXN][MAXN];
queue<int> q;

inline bool in(int x,int y) {return 0<=x&&x<n&&0<=y&&y<m;}

inline bool update(int x,int y,int s,int _x,int _y,int _s,int v)
{
    if(v<f[x][y][s])
        return f[x][y][s]=v,frm[x][y][s]=id2(_x,_y,_s),true;
    return false;
}

inline void SPFA()
{
    while(!q.empty())
    {
        int x,y,s;
        rid2(q.front(),x,y,s);q.pop();
        inq[x][y]=0;
        for(int i=0;i<4;i++)
        {
            int nx=x+mv[i][0],ny=y+mv[i][1];
            if(!in(nx,ny)) continue;
            if(update(nx,ny,s,x,y,s,f[x][y][s]+val[nx][ny])&&!inq[nx][ny])
                inq[nx][ny]=1,q.push(id2(nx,ny,s));
        }
    }
}

void dfs(int x,int y,int s)
{
    if(!frm[x][y][s]) return;
    int nx,ny,ss;
    rid2(frm[x][y][s],nx,ny,ss);
    vis[nx][ny]=1;
    dfs(nx,ny,ss);
    if(nx==x&&ny==y) dfs(nx,ny,s^ss);
}

int main()
{
    scanf("%d%d",&n,&m);
    memset(f,0x3f,sizeof f);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            scanf("%d",&val[i][j]);
            if(!val[i][j]) f[i][j][1<<(tot++)]=0;
        }
    for(int s=0;s<(1<<tot);s++)
    {
        for(int ss=(s-1)&s;ss;ss=(ss-1)&s)
            for(int i=0;i<n;i++)
                for(int j=0;j<m;j++)
                    update(i,j,s,i,j,ss,f[i][j][ss]+f[i][j][ss^s]-val[i][j]);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(f[i][j][s]!=0x3f3f3f3f)
                    q.push(id2(i,j,s)),inq[i][j]=1;
        SPFA();
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(!val[i][j])
            {
                dfs(i,j,(1<<tot)-1);
                printf("%d\n",f[i][j][(1<<tot)-1]);
                for(int x=0;x<n;x++)
                    for(int y=0;y<m;y++)
                        {
                            if(val[x][y]==0) putchar('x');
                            else if(vis[x][y]) putchar('o');
                            else putchar('_');
                            if(y==m-1) puts("");
                        }
                return 0;
            }
    #ifdef LOCAL
        system("pause");
    #endif
}