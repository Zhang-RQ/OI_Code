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

const int MAXN=510;
const int MAXQ=6E4+10;

int n,q,cnt;
int sum[MAXN][MAXN],vis[MAXN][MAXN],fa[MAXQ];

struct Number{
    int v,x,y;
    Number(){}
    Number(int _v,int _x,int _y) {v=_v;x=_x;y=_y;}
    bool operator < (const Number &rhs) const {return v<rhs.v;}
}b[MAXN*MAXN];

struct Query{
    int x1,y1,x2,y2,k,ans;
}Q[MAXQ];

int find(int x){return x>q?q+100:(x==fa[x]?x:fa[x]=find(fa[x]));}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&x),b[++cnt]=Number(x,i,j);
    for(int i=1;i<=q;i++)
        scanf("%d%d%d%d%d",&Q[i].x1,&Q[i].y1,&Q[i].x2,&Q[i].y2,&Q[i].k),fa[i]=i;
    sort(b+1,b+1+cnt);
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<=n;j++)
            vis[b[i*n+j].x][b[i*n+j].y]=1;
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
                sum[j][k]=sum[j][k-1]+sum[j-1][k]-sum[j-1][k-1]+vis[j][k];
        for(int j=find(1);j<=q;j=find(j+1))
        {
            int t=sum[Q[j].x2][Q[j].y2]-sum[Q[j].x1-1][Q[j].y2]-sum[Q[j].x2][Q[j].y1-1]+sum[Q[j].x1-1][Q[j].y1-1];
            if(t<Q[j].k) continue;
            t-=Q[j].k;
            for(int k=n;k;k--)
                if(Q[j].x1<=b[i*n+k].x&&b[i*n+k].x<=Q[j].x2&&Q[j].y1<=b[i*n+k].y&&b[i*n+k].y<=Q[j].y2)
                    if(!t--) {Q[j].ans=b[i*n+k].v;fa[j]=find(j+1);break;}
        }
    }
    for(int i=1;i<=q;i++)
        printf("%d\n",Q[i].ans);
    #ifdef LOCAL
        system("pause");
    #endif
}