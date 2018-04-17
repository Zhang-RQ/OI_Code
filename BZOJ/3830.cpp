#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1000010
using namespace std;
long long a[N],f[N];
long long c[N];
long long n,s;
void change(long long x,long long v)
{
    for(;x<=n;x+=x&-x)
    c[x]=min(c[x],v);
}
long long check(long long x)
{
    long long ans=707185547707185547LL;
    for(;x;x-=x&-x)
    ans=min(ans,c[x]);
    return ans;
}
int main()
{
    scanf("%lld%lld",&n,&s);
    long long i,j;
    scanf("%d",&a[1]);
    for(i=2;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        a[i]=max(a[i-1]+1,a[i]);
    }
    long long L,R,mid;
    memset(c,0x3f,sizeof(c));
    for(i=1;i<=n;i++)  
    {
        L=1;R=i;
        while(L<R)
        {
            mid=(L+R)>>1;
            if(f[mid]-mid-1<=a[i]-i) L=mid+1;
            else R=mid;
        }
        f[i]=a[i]-(L-1)+2*s+i-1;
        if(L!=i) f[i]=min(f[i],check(n+1-L)+2*s+2*i);
        change(n+1-i,f[i]-2*i-2);
    }
    printf("%lld",f[n]);
}
