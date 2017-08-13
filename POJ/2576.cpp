#include<cstdio>
#include<cstring>
using namespace std;
int maxn(int a,int b)
{
    if(a<b) return b;
    else return a;
}
int DP[110][30010];
int main()
{
    int sum=0,A;
    int n,W[110];//DP[i][j]表示有i人在一队，一队理想质量为j时的实际质量
    memset(DP,0,sizeof(DP));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&W[i]);
        sum+=W[i];
    }
    A=sum;
    sum=sum/2;
    int ans=-1;
    for(int i=1;i<=n;i++)
        for(int k=1;k<=i;k++)
            for(int j=sum;j>=0;j--)
            {
                if(j-W[i]>=0) DP[k][j]=maxn(DP[k][j],DP[k-1][j-W[i]]+W[i]);
            }
    if(n%2==0)  printf("%d %d\n",DP[n/2][sum],A-DP[n/2][sum]);
    else{
        if(DP[n/2][sum]>DP[n/2+1][sum]) printf("%d %d\n",DP[n/2][sum],A-DP[n/2][sum]);
            else printf("%d %d\n",DP[n/2+1][sum],A-DP[n/2+1][sum]);
    }
    return 0;
}
