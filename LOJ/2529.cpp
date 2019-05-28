#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int lg2[MAXN];

struct ST_Table{
	ll val[MAXN][19];
	int pos[MAXN],siz;

	void init(ll *v,int k)
	{
		siz=k;
		for(int i=1;i<=siz;i++)
			val[i][0]=v[i];
		for(int j=1;(1<<j)<=siz;j++)
			for(int i=1;i+(1<<j)-1<=siz;i++)
				val[i][j]=min(val[i][j-1],val[i+(1<<(j-1))][j-1]);
	}

	ll Query(int l,int r)
	{
		l=lower_bound(pos+1,pos+1+siz,l)-pos;
		r=upper_bound(pos+1,pos+1+siz,r)-pos-1;
		if(l>r) return 1ll<<60;
		int len=lg2[r-l+1];
		return min(val[l][len],val[r-(1<<len)+1][len]);
	}
}ST1,ST2;

int n,m;
ll s[MAXN],tmp[MAXN],a[MAXN],w[MAXN];
pair<ll,ll> p[MAXN];

bool chkL(int x,int pos)
{
	if(pos==x)
		return true;
	int lim=max(1,2*pos-x+1);
	if(ST2.Query(pos,x-1)<=s[x]+a[x]||ST1.Query(lim,pos)<=s[x]+a[x]-2*s[pos])
		return false;
	if(2*pos-x>=1)
		return ST1.Query(2*pos-x,2*pos-x)>s[x]+a[x]-2*s[pos];
	return true;
}

bool chkR(int x,int pos)
{
	if(pos==x)
		return true;
	int lim=min(n,2*pos-x-1);
	if(ST1.Query(x+1,pos)<=a[x]-s[x]||ST2.Query(pos,lim)<=2*s[pos]-s[x]+a[x])
		return false;
	if(2*pos-x<=n)
		return ST2.Query(2*pos-x,2*pos-x)>=2*s[pos]-s[x]+a[x];
	return true;
}

int getL(int x)
{
	int L=1,R=x,Ans=0;
	while(L<=R)
	{
		int Mid=(L+R)>>1;
		if(chkL(x,Mid)) Ans=Mid,R=Mid-1;
		else L=Mid+1;
	}
	return Ans;
}

int getR(int x)
{
	int L=x,R=n,Ans=0;
	while(L<=R)
	{
		int Mid=(L+R)>>1;
		if(chkR(x,Mid)) Ans=Mid,L=Mid+1;
		else R=Mid-1;
	}
	return Ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++)
		lg2[i]=lg2[i>>1]+1;
	for(int i=2;i<=n;i++)
		scanf("%lld",&w[i]);
	for(int i=2;i<=n;i++)
		s[i]=s[i-1]+w[i];
	while(m--)
	{
		int k;
		scanf("%d",&k);
		for(int i=1;i<=k;i++)
			scanf("%lld%lld",&p[i].first,&p[i].second);
		sort(p+1,p+1+k);
		for(int i=1;i<=k;i++)
			a[p[i].first]=p[i].second,ST1.pos[i]=ST2.pos[i]=p[i].first;
		for(int i=1;i<=k;i++)
			tmp[i]=a[p[i].first]-s[p[i].first];
		ST1.init(tmp,k);
		for(int i=1;i<=k;i++)
			tmp[i]=a[p[i].first]+s[p[i].first];
		ST2.init(tmp,k);
		ll Ans=0;
		for(int i=1;i<=k;i++)
			Ans+=(getR(p[i].first)-getL(p[i].first)+1);
		for(int i=1;i<=k;i++)
			a[p[i].first]=0;
		printf("%lld\n",Ans);
	}
}
