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

struct FastIO{
    static const int S=1e7;
    int wpos;
    char wbuf[S];
    FastIO():wpos(0){}

    inline int xchar()
    {
        static char buf[S];
        static int len=0,pos=0;
        if(pos==len)
            pos=0,len=fread(buf,1,S,stdin);
        return buf[pos++];
    }

    inline int operator () ()
    {
        int c=xchar(),x=0,ng=0;
        while (!isdigit(c)) c=xchar(),ng|=(c=='-');
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline ll operator ! ()
    {
        int c=xchar(),ng=0;ll x=0;
        while(!isdigit(c)) c=xchar(),ng|=(c=='-');
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline void wchar(int x)
    {
        if(wpos==S) fwrite(wbuf,1,S,stdout),wpos=0;
        wbuf[wpos++]=x;
    }

    inline void operator () (ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar('\n');
    }

    inline void space(ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar(' ');
    }

    inline void nextline() {wchar('\n');}

    ~FastIO() {if(wpos) fwrite(wbuf,1,wpos,stdout),wpos=0;}
}io;

const int MAXN=262144;
const int P=998244353;
const int g[2]={3,(P+1)/3};

ll ksm(ll a,ll b)
{
	ll ret=1;a%=P;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll f[MAXN],a[MAXN],b[MAXN],c[MAXN];
int rev[MAXN],T,n,p[MAXN],stk[MAXN],top;

ll inc(ll x,ll y){x+=y;return x>=P?x-P:x;}

ll dec(ll x,ll y){x-=y;return x<0?x+P:x;}

namespace Poly_Mul{ll t1[MAXN],t2[MAXN],t3[MAXN];}

void NTT(ll *a,int n,bool f)
{
	ll *ed=a+n;
	for(int i=0;i<n;i++)
		if(i>rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
	{
		ll wn=ksm(g[f],(P-1)/i);
		for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
		{
			ll w=1;
			for(int k=0;k<(i>>1);k++)
			{
				ll u=x[k],t=y[k]*w%P;
				x[k]=inc(u,t);y[k]=dec(u,t);
				w=w*wn%P;
			}
		}
	}
}

void Mul(ll *a,ll *b,ll *Res,int n,int m)
{
	using namespace Poly_Mul;
	int tot=1,lg2=0;
	while(tot<n+m) tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
	for(int i=0;i<n;i++) t1[i]=a[i];
	for(int i=0;i<m;i++) t2[i]=b[i];
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i]%P;
	NTT(t3,tot,1);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<tot;i++) Res[i]=t3[i]*inv%P;
}

void solve(int l,int r)
{
	if(l==r) return f[l]=inc(f[l],f[l-1]*(l-1)%P),void();
	int mid=(l+r)>>1;
	solve(l,mid);
	for(int i=l;i<=mid;i++)
		a[i-l]=f[i]*(i-1)%P,b[i-l]=f[i];
	Mul(a,b,c,mid-l+1,mid-l+1);
	for(int i=max(l<<1,mid+1);i<=min(r,mid<<1);i++)
		f[i]=inc(f[i],c[i-(l<<1)]);
	if(l!=2)
	{
		int lim=l+min(l-1,r-l);
		for(int i=l;i<=mid;i++)
			a[i-l]=f[i];
		for(int i=2;i<=min(l-1,r-l);i++)
			b[i-2]=f[i];
		Mul(a,b,c,mid-l+1,min(l-1,r-l)-1);
		for(int i=max(l+2,mid+1);i<=min(r,lim);i++)
			f[i]=inc(f[i],(i-2)*c[i-l-2]%P);
	}
	solve(mid+1,r);
}

int main()
{
	T=io();n=io();
	f[0]=1;f[1]=2;
	solve(2,n);
 	while(T--)
	{
		for(int i=1;i<=n;i++) p[i]=io();
		ll Ans=1;bool fl=0;top=0;
		for(int r=1;r<=n;r++)
		{
			int cnt=0;
			while(top&&stk[top]>=r-p[r]+1)
			{
				fl|=stk[top]-p[stk[top]]<r-p[r];
				++cnt;--top;
			}
			stk[++top]=r;
			Ans=Ans*f[cnt]%P;
		}
		fl|=p[n]!=n;
		io(fl?0:Ans);
	}
}