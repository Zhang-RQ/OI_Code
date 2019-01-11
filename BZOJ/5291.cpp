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

const int MAXN=2E5+10;
const int P=1E9+7;
const int inv2=5E8+4;
const int inv6=166666668;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
            x=0;static char ch=get_char();
            while(!isdigit(ch)) ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
        }

    #if __cplusplus >= 201103L
        template<typename T,typename ...Args>
            inline void read(T& x,Args& ...args)
            {
                read(x);
                read(args...);
            }
    #endif
}

using namespace FastIO;

ll S1(ll x){x%=P;return x*(x+1)%P*inv2%P;}

ll S2(ll x){x%=P;return x*(x+1)%P*(2*x+1)%P*inv6%P;}

ll S1(ll L,ll R){return (S1(R)-S1(L-1)+P)%P;}

ll S2(ll L,ll R){return (S2(R)-S2(L-1)+P)%P;}

ll inc(ll x,ll y){x+=y;return x>=P?x-P:x;}

void upd(ll &x,ll y){x=inc(x,y);}

int n,m;
ll t[MAXN<<2],ta[MAXN<<2],tb[MAXN<<2],tc[MAXN<<2],s[MAXN];

void pushup(int x){t[x]=inc(t[x<<1],t[x<<1|1]);}

void pushdown(int x,int l,int r)
{
	int mid=(l+r)>>1;
	if(ta[x])
	{
		upd(ta[x<<1],ta[x]);upd(ta[x<<1|1],ta[x]);
		upd(t[x<<1],ta[x]*S2(l,mid)%P);upd(t[x<<1|1],ta[x]*S2(mid+1,r)%P);
		ta[x]=0;
	}
	if(tb[x])
	{
		upd(tb[x<<1],tb[x]);upd(tb[x<<1|1],tb[x]);
		upd(t[x<<1],tb[x]*S1(l,mid)%P);upd(t[x<<1|1],tb[x]*S1(mid+1,r)%P);
		tb[x]=0;
	}
	if(tc[x])
	{
		upd(tc[x<<1],tc[x]);upd(tc[x<<1|1],tc[x]);
		upd(t[x<<1],tc[x]*(mid-l+1)%P);upd(t[x<<1|1],tc[x]*(r-mid)%P);
		tc[x]=0;
	}
}

void build(int x,int l,int r)
{
	if(l==r) return t[x]=s[l],void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x);
}

ll query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[x];
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(qr<=mid) return query(x<<1,l,mid,ql,qr);
	else if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
	else return inc(query(x<<1,l,mid,ql,qr),query(x<<1|1,mid+1,r,ql,qr));
}

void change(int x,int l,int r,int cl,int cr,int a,int b,int c)
{
	if(cl>cr) return;
	if(cl<=l&&r<=cr) return upd(t[x],S2(l,r)*a%P),upd(t[x],S1(l,r)*b%P),upd(t[x],1ll*(r-l+1)*c%P),upd(ta[x],a),upd(tb[x],b),upd(tc[x],c),void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,a,b,c);
	if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,a,b,c);
	pushup(x);
}

void C(int l,int r,int v)
{
	if(l>r) swap(l,r);
	change(1,0,n,l,r,1ll*v*inv2%P,1ll*v*((3-inc(l,l)+P)%P)%P*inv2%P,1ll*v*((1ll*l*l%P-3*l%P+2+P)%P)%P*inv2%P);
	int len=r-l+1;
	ll dlt=1ll*len*(len+1)%P*inv2%P*v%P;
	change(1,0,n,r+1,n,0,1ll*v%P*len%P,(dlt-1ll*len*v%P*r%P+P)%P);
}

int main()
{
	read(n,m);
	for(int i=1;i<=n;i++) read(s[i]);
	for(int i=1;i<=n;i++) upd(s[i],s[i-1]);
	for(int i=1;i<=n;i++) upd(s[i],s[i-1]);
	build(1,0,n);
	for(int i=1,op,l,r,v;i<=m;i++)
	{
		read(op);
		if(op==1) read(l,r,v),C(l,r,v);
		else
		{
			read(l,r);
			ll Ans=(r-l+1)*query(1,0,n,n,n)%P;
			upd(Ans,P-query(1,0,n,l-1,r-1));upd(Ans,P-query(1,0,n,n-r,n-l));
			printf("%lld\n",Ans);
		}
	}
}