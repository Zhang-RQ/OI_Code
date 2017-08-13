#include<cstdio>
#include<cstring>
using namespace std;
int maxn(int a,int b)
{
    if(a<b) return b;
    return a;
}
int main()
{
    int DP[100010];
    int W[250],V[250];
    int cash,n,N[15],tempv;
    int num;
    while(scanf("%d%d",&cash,&n)!=EOF)
    {
        memset(W,0,sizeof(W));
        memset(V,0,sizeof(V));
        memset(DP,0,sizeof(DP));
        num=1;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&N[i],&tempv);
            for(int j=1;j<N[i];j*=2)
            {
                W[num]=j*tempv;
                V[num++]=j*tempv;
                N[i]-=j;
            }
            if(N[i]>0)
            {
                W[num]=N[i]*tempv;
                V[num++]=N[i]*tempv;
            }
        }
        if(cash==0||n==0)//cash==0时必须录入bill数据后再continue
        {
            printf("0\n");
            continue;
        }
        for(int i=1;i<num;i++)
        {
            for(int j=cash;j>=0;j--)
            {
                if(j>=W[i]) DP[j]=maxn(DP[j],DP[j-W[i]]+V[i]);
            }
        }
        printf("%d\n",DP[cash]);
    }
    return 0;
}
