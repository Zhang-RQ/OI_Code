#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>

int main()
{
    int n,A[100010],x;
    long long ans=0;
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;i++) scanf("%d",&A[i]);
    for(int i=1;i<=n-1;i++)
    {
        if(A[i]+A[i+1]>x)
        {
            int tmp=A[i]+A[i+1]-x;
            if(A[i+1]-tmp>=0) A[i+1]-=tmp,ans+=tmp;
            else A[i+1]=0,A[i]-=tmp-A[i+1],ans+=tmp;
        }
    }
    printf("%lld\n",ans);
}
