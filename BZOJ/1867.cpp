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

const int MAXN=55;

int n,m;
char str[1001];


 
ll gcd(ll a,ll b)
{
    if(!a||!b) return a|b;
    if(a<b) return gcd(a,b%a);
    else return gcd(b,a%b);
}

struct frac{
    ll a,b;// a/b
    frac(){a=0;b=1;}
    frac(ll _,ll __){a=_;b=__;}
    inline frac reduc() const
    {
        ll d=gcd(a,b);
        return frac(a/d,b/d);
    }
    inline frac operator + (const frac &rhs) const
    {
        ll d=gcd(b,rhs.b);
        return frac(rhs.b/d*a+b/d*rhs.a,b/d*rhs.b).reduc();
    }
    inline frac operator * (const frac &rhs) const {return frac(a*rhs.a,b*rhs.b).reduc();}
    inline frac operator += (const frac &rhs) {return *this=*this+rhs;}
    inline void print(){printf("%lld/%lld",a,b);}
}f[MAXN][MAXN],half;

int main()
{
    half=frac(1,2);
    f[1][1]=frac(1,1);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            scanf("%s",str+1);
            if(str[1]=='*') f[i+1][j]+=f[i][j]*half,f[i+1][j+1]+=f[i][j]*half;
            else f[i+2][j+1]+=f[i][j];
        }
    }
    f[n+1][m+1].print();
    #ifdef LOCAL
        system("pause");
    #endif
}