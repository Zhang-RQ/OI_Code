// TLE
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
struct Matrix{
    double a[3][3];
    inline Matrix operator * (const Matrix &rhs)
    {
        Matrix ret;
        memset(ret.a,0,sizeof ret.a);
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    ret.a[i][j]+=a[i][k]*rhs.a[k][j];
        return ret;
    }
}t,ans,tt;
Matrix ksm(Matrix a,int b)
{
    Matrix ret;
    memset(ret.a,0,sizeof ret.a);
    for(int i=0;i<3;i++)
        ret.a[i][i]=1;
    while(b)
    {
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}
int n,x[15],lst;
double p;
int main()
{
    while(scanf("%d%lf",&n,&p)!=EOF)
    {
        t.a[0][0]=p;  t.a[0][1]=1;
        t.a[1][0]=1-p;t.a[1][1]=0;
        ans.a[0][0]=1;ans.a[0][1]=0;
        ans.a[1][0]=0;ans.a[1][1]=0;
        lst=1;
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        sort(x+1,x+1+n);
        for(int i=1;i<=n;i++)
        {
            tt=ksm(t,x[i]-1-lst);lst=x[i]+1;
            ans=ans*tt;
            ans.a[0][0]=ans.a[0][0]*(1-p);ans.a[0][1]=0;
            ans.a[1][0]=0;               ans.a[1][1]=0;
        }
        printf("%.7lf\n",ans.a[0][0]);
    }
}
