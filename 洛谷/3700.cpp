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
namespace FastIO
{
    const int Bufsiz=1<<22;	// buffer size
    inline char get_c() {
        static char buf[Bufsiz];	// buffer
        static char *head = buf + Bufsiz;
        static char *tail = buf + Bufsiz;
        if (head == tail)	// at the end of buffer
        tail = buf + fread(head = buf, 1, BUFSIZ, stdin);	// reload from STDIN
        return *head++;
    }
    inline ll get_i() {
        ll res = 0;	// result
        int isn = 0; 	// is negative
        int chr = get_c();	// current char
        for (; chr < 48; chr = get_c())
        if (chr == '-')isn ^= 1;
        for (; chr > 47; chr = get_c())
        res = res * 10 + chr - 48;
        return isn ? -res : res;
    }
}
using namespace std;
using namespace FastIO;
const int MAXN=4E6+10;
const int P=1E9+7;
int prime[MAXN],cnt,phi[MAXN],n,arr[MAXN],m,G[MAXN],a,b,k;
int bl[MAXN],blocksiz;
ll x;
unsigned char vis[MAXN];
struct Block{
    int sum[2010],ans;
    int st,ed;
}blk[2010];
int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int ksm(int a,int b)
{
    int ret=1;
    while(b)
    {
        if(b&1) ret=1ll*ret*a%P;
        a=1ll*a*a%P;
        b>>=1;
    }
    return ret;
}
void build(int x)
{
    blk[x].sum[0]=arr[blk[x].st];
    for(int i=1;i<=blk[x].ed-blk[x].st;i++) blk[x].sum[i]=(1ll*blk[x].sum[i-1]+arr[i+blk[x].st])%P;
    blk[x].ans=(blk[x-1].ans+blk[x].sum[blk[x].ed-blk[x].st])%P;
}
void init()
{
    for(int i=1;i<=n;i++) arr[i]=1ll*i*i%P;
    for(int i=1;i<=n;i++)
    {
        bl[i]=(i-1)/blocksiz+1;
        if(!blk[bl[i]].st) blk[bl[i]].st=i;
        blk[bl[i]].ed=i;
    }
    for(int i=1;i<=bl[n];i++) build(i);
}
int query(int R)
{
    int b=bl[R],ret=blk[b-1].ans%P;
    ret=(1ll*ret+blk[b].sum[R-blk[b].st])%P;
    return ret;
}
void get()
{
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]) {prime[++cnt]=i;phi[i]=i-1;}
        for(int j=1;j<=cnt&&prime[j]*i<=n;j++)
        {
            vis[prime[j]*i]=1;
            if(i%prime[j]==0) {phi[i*prime[j]]=phi[i]*prime[j];break;}
            else phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
    for(int i=1;i<=n;i++) G[i]=(G[i-1]+1ll*i*i%P*phi[i]%P)%P;
}
signed main()
{
    m=get_i();n=get_i();
    blocksiz=sqrt(n);
    init();get();
    int d,ans=0;
    for(int i=1;i<=m;i++)
    {
        ans=0;
        a=get_i();b=get_i();x=get_i();k=get_i();
        x%=P;d=gcd(a,b);
        arr[d]=1ll*x*d%P*d%P*ksm(1ll*a*b%P,P-2)%P;
        build(bl[d]);
        for(int i=bl[d]+1;i<=bl[n];i++)
            blk[i].ans=(blk[i-1].ans+blk[i].sum[blk[i].ed-blk[i].st])%P;
        for(int j=1,nxt;j<=k;j=nxt+1)
        {
            nxt=k/(k/j);
            ans=(ans+1ll*((query(nxt)-query(j-1))%P+P)%P*G[k/j]%P)%P;
        }
        ans=(ans%P+P)%P;
        printf("%d\n",ans);
    }
}
