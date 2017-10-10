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
int DP[1010][110];
int up[1010],down[1010];
int tup[1010],tdown[1010];
bool thave[1010],ok[1010];
int n,m,k,t1,t2,t3;
int main()
{
    memset(DP,0x3f,sizeof(DP));
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<m;i++) DP[0][i]=0;
    for(int i=0;i<n;i++) scanf("%d%d",&up[i],&down[i]);
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d%d",&t1,&t2,&t3);
        thave[t1]=1;
        tdown[t1]=t2+1;tup[t1]=t3-1;
    }
    for(int i=1;i<n;i++) if(!thave[i]) tup[i]=m;
    for(int i=1;i<=n;i++)
    {
        for(int j=tdown[i];j<=tup[i];j++)
        {
            if(j>=up[i-1])
                    DP[i][j]=min(DP[i][j],min(DP[i-1][j-up[i-1]],DP[i][j-up[i-1]])+1);
            if(DP[i][j]!=0x3f3f3f3f) ok[i]=1;
        }
        for(int j=tdown[i];j<=tup[i];j++)
        {
            if(j+down[i-1]<=m)
                DP[i][j]=min(DP[i][j],DP[i-1][j+down[i-1]]);
            if(DP[i][j]!=0x3f3f3f3f) ok[i]=1;
        }
    }
    int ans=0x3f3f3f3f;
    for(int i=0;i<=m;i++)  ans=min(ans,DP[n][i]);
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++) printf("%d ",DP[i][j]);
        puts("");
    }
    if(ans!=0x3f3f3f3f)  printf("%d\n",ans);
    else{
        printf("0\n");
        for(int i=n;i>=0;i--) if(ok[i]) {printf("%d\n",i);break;}
    }
}
