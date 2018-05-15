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
const int MAXN=10010;
int sg[MAXN],T,n,ans,x,Cs;
bool vis[65565];
void get_sg()
{
    sg[1]=0;
    for(int i=2;i<MAXN;i++)
    {
        memset(vis,0,sizeof vis);
        for(int j=1;j*2<i;j++)
            vis[sg[j]^sg[i-j]]=1;
        for(int j=0;j<i;j++)
            if(!vis[j]) {sg[i]=j;break;}
    }
}
int main()
{
    get_sg();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ans=0;
        for(int i=1;i<=n;i++) scanf("%d",&x),ans^=sg[x];
        printf("Case %d: ",++Cs);
        puts(ans?"Alice":"Bob");
    }
}
