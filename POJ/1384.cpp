#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    int F[10010],P[510],W[510];
    int T,n,m,weight,N,temp;
    scanf("%d",&T);
    while(T--)
    {
        memset(F,0,sizeof(F));
        scanf("%d%d%d",&n,&m,&N);
        for(int i=1;i<=N;i++) scanf("%d%d",&P[i],&W[i]);
        weight=m-n;
        for(int i=1;i<=weight;i++)
        {
            temp=0x3f3f3f3f;
            for(int j=1;j<=N;j++)
            {
                if(i-W[j]<0) continue;
                if(F[i-W[j]]+P[j]<temp) temp=F[i-W[j]]+P[j];
                //printf("%d ",temp);
            }
            F[i]=temp;
        }
        if(F[weight]==0x3f3f3f3f)
        {
                printf("This is impossible.\n");
                continue;
        }
        printf("The minimum amount of money in the piggy-bank is %d.\n",F[weight]);
    }
    return 0;
}
