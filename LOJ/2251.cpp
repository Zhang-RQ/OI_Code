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

const int MAXN=1E5+10;
const int P=998244353;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

struct node_t{
	int l,r,v;
}t[MAXN*400];

int rt,rt2,cnt,n,m;

ll Calc(ll x,ll y){return (x*(P+1-y)%P+y*(P+1-x)%P)%P;}

void Change1(int &x,int l,int r,int cl,int cr,ll dlt)
{
	if(!x) x=++cnt;
	if(cl<=l&&r<=cr) return t[x].v=Calc(t[x].v,dlt),void();
	int mid=(l+r)>>1;
	if(cl<=mid) Change1(t[x].l,l,mid,cl,cr,dlt);
	if(cr>mid)  Change1(t[x].r,mid+1,r,cl,cr,dlt);
}

void Change2(int &x,int l,int r,int cl1,int cr1,int cl2,int cr2,ll dlt)
{
	if(!x) x=++cnt;
	if(cl1<=l&&r<=cr1) return Change1(t[x].v,1,n,cl2,cr2,dlt);
	int mid=(l+r)>>1;
	if(cl1<=mid) Change2(t[x].l,l,mid,cl1,cr1,cl2,cr2,dlt);
	if(cr1>mid)  Change2(t[x].r,mid+1,r,cl1,cr1,cl2,cr2,dlt);
}

ll Query1(int x,int l,int r,int p)
{
	if(!x) return 0;
	if(l==r) return t[x].v;
	int mid=(l+r)>>1;
	if(p<=mid) return Calc(Query1(t[x].l,l,mid,p),t[x].v);
	else return Calc(Query1(t[x].r,mid+1,r,p),t[x].v);
}

ll Query2(int x,int l,int r,int p,int q)
{
	if(!x) return 0;
	if(l==r) return Query1(t[x].v,1,n,q);
	int mid=(l+r)>>1;
	if(p<=mid) return Calc(Query2(t[x].l,l,mid,p,q),Query1(t[x].v,1,n,q));
	else return Calc(Query2(t[x].r,mid+1,r,p,q),Query1(t[x].v,1,n,q));
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,op,l,r;i<=m;i++)
	{
		scanf("%d%d%d",&op,&l,&r);
		if(op==1)
		{
			ll inv=ksm(r-l+1,P-2);
			Change2(rt,1,n,l,r,l,r,2*inv%P);
			if(r<n) Change2(rt,1,n,l,r,r+1,n,inv);
			if(l>1) Change2(rt,1,n,1,l-1,l,r,inv);
			if(l>1) Change1(rt2,1,n,1,l-1,1);
			if(r<n) Change1(rt2,1,n,r+1,n,1);
			Change1(rt2,1,n,l,r,(1-inv+P)%P);
		}
		else
		{
			if(l!=1) printf("%lld\n",(1-Query2(rt,1,n,l-1,r)+P)%P);
			else printf("%lld\n",(1-Query1(rt2,1,n,r)+P)%P);
		}
	}
}
