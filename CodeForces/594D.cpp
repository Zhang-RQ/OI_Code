#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXA=1E6+10;
const int MAXN=2E5+10;
const int P=1E9+7;

bool vis[MAXA];
int pr[MAXA],pc,lst[MAXA],minp[MAXA],n,q;
ll t[MAXN],Ans[MAXN];
vector<pair<int,int> > v[MAXN],vq[MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void sieve()
{
	for(int i=2;i<MAXA;i++)
	{
		if(!vis[i]) pr[++pc]=i,minp[i]=i;
		for(int j=1;i*pr[j]<MAXA&&j<=pc;j++)
		{
			vis[i*pr[j]]=1;
			minp[i*pr[j]]=pr[j];
			if(!(i%pr[j])) break;
		}
	}
}

void C(int x,ll v)
{
	for(;x<=n;x+=x&(-x))
		t[x]=t[x]*v%P;
}

ll Q(int x)
{
	if(!x) return 1;
	ll ret=1;
	for(;x;x-=x&(-x))
		ret=ret*t[x]%P;
	return ret;
}

void C(int l,int r,ll v){C(l,v);C(r+1,ksm(v,P-2));}

int main()
{
	scanf("%d",&n);
	sieve();
	for(int i=1;i<=n;i++) t[i]=1;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		while(x!=1)
		{
			int p=minp[x],cnt=0;
			while(!(x%p)) x/=p,++cnt;
			v[i].emplace_back(p,cnt);
		}
	}
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		vq[r].emplace_back(l,i);
	}
	for(int r=1;r<=n;r++)
	{
		for(auto x:v[r])
		{
			ll t=ksm(x.first,x.second-1);
			C(lst[x.first]+1,r,(x.first-1)*t%P);
			if(lst[x.first]) C(1,lst[x.first],t*x.first%P);
			lst[x.first]=r;
		}
		for(auto x:vq[r])
			Ans[x.second]=Q(x.first);
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",Ans[i]);
}
