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
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int P=998244353;
const int rev=499122177;

void FWT(int *a,int n,int tp) //1,xor 2,and 3,or
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=0;k<(i>>1);k++)
            {
                ll x=a[j+k],y=a[j+k+(i>>1)];
                if(tp==1) a[j+k]=x,a[j+k+(i>>1)]=(x+y)%P;
                if(tp==2) a[j+k]=(x+y)%P,a[j+k+(i>>1)]=y;
                if(tp==3) a[j+k]=(x+y)%P,a[j+k+(i>>1)]=(x-y+P)%P;
            }
}

void UFWT(int *a,int n,int tp)
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=0;k<(i>>1);k++)
            {
                ll x=a[j+k],y=a[j+k+(i>>1)];
                if(tp==1) a[j+k]=x,a[j+k+(i>>1)]=(y-x+P)%P;
                if(tp==2) a[j+k]=(x-y+P)%P,a[j+k+(i>>1)]=y;
                if(tp==3) a[j+k]=1LL*(x+y)*rev%P,a[j+k+(i>>1)]=(1LL*(x-y)*rev%P+P)%P;
            }
}

void solve(int a[],int b[],int n,int tp)
{
    FWT(a,n,tp);
    FWT(b,n,tp);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%P;
    UFWT(a,n,tp);
    for(int i=0;i<n;i++) printf("%d%c",a[i],i==n-1?'\n':' ');
}

const int MAXN=17;

int a[1<<MAXN],b[1<<MAXN],n;
int aa[1<<MAXN],bb[1<<MAXN];

int main()
{
    scanf("%d",&n);
    int lim=1<<n;
    for(int i=0;i<lim;i++) scanf("%d",&a[i]);
    for(int i=0;i<lim;i++) scanf("%d",&b[i]);
    for(int i=1;i<=3;i++)
    {
        memcpy(aa,a,sizeof(int)*lim);
        memcpy(bb,b,sizeof(int)*lim);
        solve(aa,bb,lim,i);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}