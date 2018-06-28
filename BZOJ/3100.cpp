#include<cstdio>
#include<bitset>
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

typedef unsigned int uint;

const int MAXN=1E6+10;

int n,ans,mx,L,mxx;
int a[MAXN],lst[MAXN];
uint sum[MAXN];
std::bitset<MAXN> vis;

inline void swap(int &a,int &b) {a^=b;b^=a;a^=b;}

bool judge(int r)
{
    int l=r-mx+1;
    if(l<=0) return 0;
    return sum[r]-sum[l-1]==(uint)mx*(1+mx)/2&&L<=l&&mxx<l;
}

void solve()
{
    int tans=0;
    for(int i=1;i<=n;i++)
        lst[i]=sum[a[i]],sum[a[i]]=i;
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    int x=0,nxt;
    for(int i=1;i<=n;i++)
        if(a[i]==1) {x=i;break;}
    while(x)
    {
        L=x;mx=mxx=0;
        nxt=0;vis[1]=1;
        while(L>0)
        {
            if(vis[a[L-1]]) break;
            vis[a[--L]]=1;
        }
        for(int i=L;i<=x;i++) vis[a[i]]=0;
        for(int i=x;i<=n;i++)
        {
            if(i!=x&&a[i]==1) {nxt=i;break;}
            mx=max(mx,a[i]);
            mxx=max(mxx,lst[i]);
            if(judge(i)) tans=max(mx,tans);
        }
        x=nxt;
    }
    ans=max(tans,ans);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    solve();
    for(int i=1;i<=(n>>1);i++)
    {
        swap(a[i],a[n-i+1]);
        sum[i]=sum[n-i]=0;
    }
    if(n&1) sum[(n>>1)+1]=0;
    solve();
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}