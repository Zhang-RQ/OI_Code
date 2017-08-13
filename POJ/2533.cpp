#include<cstdio>
#include<cstring>
using namespace std;
int maxi(int a,int b)
{
    if(a<b) return b;
    else return a;
}
int main()
{
    int n,N[1010];
    int F[1010];
    memset(F,0,sizeof(F));
    scanf("%d",&n);
    int ans=0;
    for(int i=1;i<=n;i++) scanf("%d",&N[i]);
    for(int i=1;i<=n;i++)
    {
        int maxn=0;
        for(int j=1;j<i;j++)
            if(N[j]<N[i]&&F[j]>maxn) maxn=F[j];
        F[i]=maxn+1;
        if(ans<F[i]) ans=F[i];
    }
    printf("%d\n",ans);
}
