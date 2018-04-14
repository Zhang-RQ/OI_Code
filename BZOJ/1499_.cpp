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
const int MAXN=210;
struct node{
    int l,r,t;
}a[MAXN];
int f[MAXN][MAXN][MAXN],n,m,x,y,K;
char mp[MAXN][MAXN];
deque<int> q;
int main()
{
    memset(f,0xcf,sizeof f);
    scanf("%d%d%d%d%d",&n,&m,&x,&y,&K);
    f[0][x][y]=0;
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    for(int i=1;i<=K;i++)
        scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].t);
    for(int i=1;i<=K;i++)
    {
        if(a[i].t==2)
        {
            for(int k=1;k<=m;k++)
            {
                q.clear();
                for(int j=1;j<=n;j++)
                {
                    if(mp[j][k]=='x') {q.clear();continue;}
                    while(q.size()&&j-q.front()>a[i].r-a[i].l+1) q.pop_front();
                    while(q.size()&&f[i-1][q.back()][k]-q.back()<=f[i-1][j][k]-j) q.pop_back();
                    q.push_back(j);
                    f[i][j][k]=f[i-1][q.front()][k]-q.front()+j;
                }
            }
        }
        else if(a[i].t==1)
        {
            for(int k=1;k<=m;k++)
            {
                q.clear();
                for(int j=n;j>=1;j--)
                {
                    if(mp[j][k]=='x') {q.clear();continue;}
                    while(q.size()&&q.front()-j>a[i].r-a[i].l+1) q.pop_front();
                    while(q.size()&&f[i-1][q.back()][k]+q.back()<=f[i-1][j][k]+j) q.pop_back();
                    q.push_back(j);
                    f[i][j][k]=f[i-1][q.front()][k]+q.front()-j;
                }
            }
        }
        else if(a[i].t==4)
        {
            for(int j=1;j<=n;j++)
            {
                q.clear();
                for(int k=1;k<=m;k++)
                {
                    if(mp[j][k]=='x') {q.clear();continue;}
                    while(q.size()&&k-q.front()>a[i].r-a[i].l+1) q.pop_front();
                    while(q.size()&&f[i-1][j][q.back()]-q.back()<=f[i-1][j][k]-k) q.pop_back();
                    q.push_back(k);
                    f[i][j][k]=f[i-1][j][q.front()]-q.front()+k;
                }
            }
        }
        else if(a[i].t==3)
        {
            for(int j=1;j<=n;j++)
            {
                q.clear();
                for(int k=m;k>=1;k--)
                {
                    if(mp[j][k]=='x') {q.clear();continue;}
                    while(q.size()&&q.front()-k>a[i].r-a[i].l+1) q.pop_front();
                    while(q.size()&&f[i-1][j][q.back()]+q.back()<=f[i-1][j][k]+k) q.pop_back();
                    q.push_back(k);
                    f[i][j][k]=f[i-1][j][q.front()]+q.front()-k;
                }
            }
        }
        // for(int j=1;j<=n;j++)
        // {
        //     for(int k=1;k<=m;k++)
        //         printf("%d ",f[i][j][k]);
        //     puts("");
        // }
        // puts("");
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans=max(ans,f[K][i][j]);
    printf("%d\n",ans);
}
