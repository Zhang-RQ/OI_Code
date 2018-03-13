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
const int MAXN=10;
int mod[MAXN],a[MAXN];
void exgcd(int a,int b,ll &x,ll &y)
{
    if(!b) {x=1;y=0;return;}
    exgcd(b,a%b,x,y);
    ll t=y;
    y=x-(a/b)*y;
    x=t;
}
ll CRT(int n,int d)
{
    ll ret=0,M=1;
    for(int i=1;i<=n;i++)  M*=mod[i];
    for(int i=1;i<=n;i++)
    {
        ll inv=0,t=0;
        exgcd(M/mod[i],mod[i],inv,t);
        (inv+=mod[i])%=mod[i];
        (ret+=a[i]*M/mod[i]*inv)%=M;
    }
    if(ret==0) return 21252-d;
    return (ret-d+M)%M;
}
int main()
{
    int p,e,i,d,t=0;
    mod[1]=23;mod[2]=28;mod[3]=33;
    while(~scanf("%d%d%d%d",&p,&e,&i,&d)&&p!=-1)
    {
        a[1]=p;a[2]=e;a[3]=i;
        printf("Case %d: the next triple peak occurs in %lld days.\n",++t,CRT(3,d));
    }
}
