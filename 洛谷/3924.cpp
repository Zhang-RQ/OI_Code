// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>

typedef long long ll;

using namespace std;

const int MAXN=1E6+10;

int gcd(int a,int b){return b?gcd(b,a%b):a;}

int mxd,dep[MAXN],a[MAXN],n,m,qwq;
ll Ans,s[MAXN];

int build(int x,int l,int r,int d)
{
    if(l==r) return mxd=max(d,mxd),dep[l]=d,Ans+=a[l]*(1<<(mxd-d)),a[l];
    int mid=(l+r)>>1;
    int ret=(build(x<<1,l,mid,d+1)+build(x<<1|1,mid+1,r,d+1));
    Ans+=ret*(1ll<<(mxd-d));
    return ret;
}

int main()
{
    scanf("%d%d%d",&n,&m,&qwq);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n,0);int O=1<<mxd,d=gcd(O,qwq);
    O/=d;qwq/=d;
    for(int i=1;i<=n;i++) s[i]=s[i-1]+(1<<(mxd+1))-(1<<(mxd-dep[i]));
    for(int i=1,x,l,r;i<=m;i++)
    {
        scanf("%d%d%d",&l,&r,&x);
        Ans+=(s[r]-s[l-1])*x;
        printf("%lld\n",Ans*qwq/O);
    }
}