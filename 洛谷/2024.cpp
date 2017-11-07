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
const int MAXN=100100;
int fa[MAXN],dis[MAXN];
int n,m,opt,ans,x,y;
int find(int x)
{
    if(fa[x]==x)
        return x;
    else
    {
        int f=fa[x];
        fa[x]=find(fa[x]);
        (dis[x]+=dis[f])%=3;  //0同类   1被吃    2吃 (节点与根)
    }
    return fa[x];
}
bool add(int x,int y,int opt)  //x--(opt)-->y
{
    int fx=find(x),fy=find(y);
    if(fx!=fy)
    {
        fa[fx]=fy;
        dis[fx]=(dis[y]-dis[x]+3+opt-1)%3;
        return true;
    }
    else
    {
        if(opt==1)
        {
            if(dis[x]!=dis[y])
                return false;
        }
        else
        {
            if(dis[x]==0&&dis[y]!=2)
                return false;
            if(dis[x]==1&&dis[y]!=0)
                return false;
            if(dis[x]==2&&dis[y]!=1)
                return false;
        }
        return true;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&opt,&x,&y);
        if(x>n||y>n)
            {++ans;continue;}
        if(opt==2&&x==y)
            {++ans;continue;}
        if(!add(x,y,opt))
            ++ans;
    }
    printf("%d\n",ans);
}
