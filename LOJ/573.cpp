#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

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

const int P=998244353;
const int MAXN=1E6+10;

struct Mat{
	ll a[2][2];

	Mat(){memset(a,0,sizeof a);}

	ll* operator [] (int x){return a[x];}
	const ll* operator [] (int x) const {return a[x];}

	void set(ll v) {a[0][0]=v;a[0][1]=a[1][0]=1;}
	
	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		ret[0][0]=(a[0][0]*rhs[0][0]+a[0][1]*rhs[1][0])%P;
		ret[0][1]=(a[0][0]*rhs[0][1]+a[0][1]*rhs[1][1])%P;
		ret[1][0]=(a[1][0]*rhs[0][0]+a[1][1]*rhs[1][0])%P;
		ret[1][1]=(a[1][0]*rhs[0][1]+a[1][1]*rhs[1][1])%P;
		return ret;
	}
}t[MAXN<<2];

int n,m,tp,a[MAXN];

void build(int x,int l,int r)
{
	if(l==r)
		return t[x].set(a[l]),void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	if(mid+1<=n)
		build(x<<1|1,mid+1,r),t[x]=t[x<<1|1]*t[x<<1];
}

void insert(int x,int l,int r,int p,int v)
{
	if(l==r)
		return t[x].set(v),void();
	int mid=(l+r)>>1;
	if(p<=mid)
		insert(x<<1,l,mid,p,v);
	else
		insert(x<<1|1,mid+1,r,p,v);
	if(p==r)
		t[x]=t[x<<1|1]*t[x<<1];
}

Mat query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
		return t[x];
	int mid=(l+r)>>1;
	if(qr<=mid)
		return query(x<<1,l,mid,ql,qr);
	else if(ql>mid)
		return query(x<<1|1,mid+1,r,ql,qr);
	else
		return query(x<<1|1,mid+1,r,ql,qr)*query(x<<1,l,mid,ql,qr);
}

int main()
{
	read(n,m,tp);
	int lim=n+m;
	for(int i=1;i<=n;i++)
		read(a[i]);
	build(1,1,lim);
	ll lstAns=0;
	for(int i=1,opt,x,y;i<=m;i++)
	{
		read(opt);
		if(opt==1)
		{
			read(x);x^=lstAns;
			insert(1,1,lim,++n,x);
		}
		else
		{
			read(x,y);x^=lstAns;y^=lstAns;
			Mat tmp;tmp[0][0]=1;
			tmp=tmp*query(1,1,lim,x,y);
			printf("%lld %lld\n",tmp[0][0],tmp[0][1]);
			if(tp)
				lstAns=tmp[0][0]^tmp[0][1];
		}
	}
}
