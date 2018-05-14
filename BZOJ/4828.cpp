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
const int MAXN=101;
const int MAXMC=101;
int n,m,mc,a[MAXN],w[MAXN],N;
int f[MAXN][MAXMC],tot,mx,C;
struct Node{int i,F,L;};
pair<int,int> zt[1111111];
int MOD=1000007;
struct Hash
{
    struct Line{int x,y,next;}e[1111111];
    int h[1000007+1],cnt;
    void Add(int x,int y)
    {
        int pos=(1ll*x*101+y)%MOD;
        e[++cnt]=(Line){x,y,h[pos]};h[pos]=cnt;
    }
    bool Query(int x,int y)
    {
        int pos=(1ll*x*101+y)%MOD;
        for(int i=h[pos];i;i=e[i].next)
            if(e[i].x==x&&e[i].y==y)return true;
        return false;
    }
}Map;
void BFS()
{
    queue<Node> Q;Q.push((Node){1,1,0});
    while(!Q.empty())
    {
        Node u=Q.front();Q.pop();
        if(u.i==N)continue;
        Q.push((Node){u.i+1,u.F,u.L+1});
        if(u.L>1&&1ll*u.F*u.L<=100000000ll&&!Map.Query(u.F*u.L,u.i+1))
        {
            Q.push((Node){u.i+1,u.F*u.L,u.L});
            zt[++tot]=make_pair(u.F*u.L,u.i+1);
            Map.Add(u.F*u.L,u.i+1);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&mc);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    f[0][mc]=0;
    for(int i=1;i<=n;++i)
        for(int j=a[i];j<=mc;++j)
            f[i][j-a[i]]=max(f[i-1][j]+1,f[i][j-a[i]]),
            f[i][min(j-a[i]+w[i],mc)]=max(f[i-1][j],f[i][min(j-a[i]+w[i],mc)]);
    for(int j=1;j<=n;j++)
        for(int i=0;i<=mc;i++) N=max(N,f[j][i]);
    BFS();
    sort(zt+1,zt+1+tot);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&C);
        if(C<=N){puts("1");continue;}
        bool fl=false;int mm=1e9;
        for(int j=tot,k=1;j;--j)
        {
            while(k<tot&&zt[k].first+zt[j].first<=C)
                mm=min(mm,zt[k].second-zt[k].first),++k;
            if(mm+C-zt[j].first<=N-zt[j].second) {fl=true;break;}
            if(zt[j].first<=C&&C-zt[j].first<=N-zt[j].second){fl=true;break;}
        }
        fl?puts("1"):puts("0");
    }
}
