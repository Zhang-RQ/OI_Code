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
const int MAXN=21;
int M[MAXN],n,S;
int f[MAXN][9010];
int dfs(int x,int res)
{
    if(f[x][res]!=-1) return f[x][res];
    if(res==1) return f[x][res]=0;
    if(res+1<=M[x]) return f[x][res]=1;
    int ret=0;
    for(int i=1;i<=M[x]&&i<=res;i++)
        if(!dfs((x+1)%n,res-i)) ret=1;
    return f[x][res]=ret;
}
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        memset(f,-1,sizeof f);
        scanf("%d",&S);
        n<<=1;
        for(int i=0;i<n;i++) scanf("%d",&M[i]);
        printf("%d\n",dfs(0,S));
    }
}
