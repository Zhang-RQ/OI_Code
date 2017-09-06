#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
long long x[100100],r[100100],summ[100100];
int main()
{
    long long sum=0,ans=0;
    int L,N;
    int pos;
    scanf("%d%d",&L,&N);
    for(int i=1;i<=N;i++)
        scanf("%lld%lld",&x[i],&r[i]),sum+=r[i],summ[i]=sum;
    long long posr=(sum/2)+(sum%2);
    for(int i=1;i<=N;i++)
        if(summ[i]>=posr)
        {
            pos=i;
            break;
        }
    for(int i=1;i<=N;i++)
    {
        ans+=abs(x[i]-x[pos])*r[i];
    }
    //printf("%lld\n",posr);
    printf("%lld\n",ans);
}
