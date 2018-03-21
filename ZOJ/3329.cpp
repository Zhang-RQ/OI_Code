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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int T,k1,k2,k3,a,b,c,n;
double A[1005],B[1005],p[1005];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d%d%d",&n,&k1,&k2,&k3,&a,&b,&c);
        memset(p,0,sizeof p);memset(A,0,sizeof A);memset(B,0,sizeof B);
        p[0]=1.0/(k1*k2*k3);
        for(int i=1;i<=k1;i++)
            for(int j=1;j<=k2;j++)
                for(int k=1;k<=k3;k++)
                    if(i!=a||j!=b||k!=c)
                        p[i+j+k]+=p[0];
        for(int i=n;i>=0;i--)
        {
            for(int k=3;k<=k1+k2+k3;k++)
            {
                A[i]+=A[i+k]*p[k];
                B[i]+=B[i+k]*p[k];
            }
            A[i]+=p[0];
            B[i]+=1;
        }
        printf("%.15lf\n",B[0]/(1-A[0]));
    }
}
