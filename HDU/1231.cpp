#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    int F[10010];
    int start[10010];
    int n,N[10010];
    while(1)
    {
        bool flag=true;
        scanf("%d",&n);
        if(n==0){
            break;
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&N[i]);
            if(N[i]>=0) flag=false;
        }
        if(flag){
            printf("0 %d %d\n",N[1],N[n]);
            continue;
        }
        memset(F,0,sizeof(F));
        for(int i=1;i<=n;i++)
        {
            if(F[i-1]<=0){
                F[i]=N[i];
                start[i]=i;
            }else{
                F[i]=F[i-1]+N[i];
                start[i]=start[i-1];
            }
        }
        int ans=0;
        int ans_end;
        for(int i=n;i>=1;i--)
        {
            if(F[i]>=ans)
            {
                ans_end=i;
                ans=F[i];
            }
        }
        printf("%d %d %d\n",ans,N[start[ans_end]],N[ans_end]);
    }
    return 0;
}
