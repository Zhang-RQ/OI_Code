#include<cstdio>
#include<memory.h>
typedef long long ll;
using namespace std;
const int P=9999973;
ll F[110][110][110];//前i行，放一个列j个，放2个列k个
int A2(int b)
{
    if(b==0) return 0;
    return b*(b-1);
}
int C2(int b)
{
    if(b==0) return 0;
    return A2(b)/2;
}
int main()
{
    int n,m;
    ll ans=0;
    scanf("%d%d",&n,&m);
    int i,j,k;
    memset(F,0,sizeof(F));
    F[0][0][0]=1;
    for(i=1;i<=n;i++)
    {
        for(j=0;j<=m;j++)
        {
            for(k=0;k<=m-j;k++)
            {
                F[i][j][k]+=F[i-1][j][k];//0
                if(j!=0) F[i][j][k]+=(F[i-1][j-1][k]*(m-j-k+1));//1->0
                if(k!=0) F[i][j][k]+=F[i-1][j+1][k-1]*(j+1);//1->1
                if(j>=2) F[i][j][k]+=F[i-1][j-2][k]*(C2(m-j-k+2));//2->0,0
                if(k>=2) F[i][j][k]+=F[i-1][j+2][k-2]*C2(j+2);//2->1,1
                if(k!=0) F[i][j][k]+=F[i-1][j][k-1]*j*(m-j-k+1);//2->1,0
                F[i][j][k]%=P;
                if(i==n) ans=(ans+F[i][j][k])%P;
            }
        }
    }
    printf("%lld\n",ans);
}