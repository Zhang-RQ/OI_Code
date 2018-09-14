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

const int MAXN=5E5+10;

int n;
vector<int> v[MAXN];
ll Ans=0;

struct node{
	ll s,S;
	int tag;
	bool cls;
}t[MAXN<<3];

void pushup(int x){t[x].s=t[x<<1].s+t[x<<1|1].s;t[x].S=t[x<<1].S+t[x<<1|1].S;}

void pushdown(int x,int l,int r)
{
	if(t[x].cls)
	{
		t[x<<1].s=t[x<<1].S=t[x<<1].tag=0;
		t[x<<1|1].s=t[x<<1|1].S=t[x<<1|1].tag=0;
		t[x<<1].cls=t[x<<1|1].cls=1;
		t[x].cls=0;
	}
	if(t[x].tag)
	{
		int mid=(l+r)>>1;
		t[x<<1].s+=1ll*(mid-l+1)*t[x].tag;
		t[x<<1].S+=1ll*(l+mid)*(mid-l+1)/2*t[x].tag;
		t[x<<1|1].s+=1ll*(r-mid)*t[x].tag;
		t[x<<1|1].S+=1ll*(mid+1+r)*(r-mid)/2*t[x].tag;
		t[x<<1].tag+=t[x].tag;t[x<<1|1].tag+=t[x].tag;
		t[x].tag=0;
	}
}

void change(int x,int l,int r,int cl,int cr,int val)
{
	if(cl<=l&&r<=cr) return t[x].tag+=val,t[x].s+=(r-l+1)*val,t[x].S+=1ll*(l+r)*(r-l+1)/2*val,void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
	if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
	pushup(x);
}

pair<ll,ll> operator + (const pair<ll,ll> &lhs,const pair<ll,ll> &rhs){return make_pair(lhs.first+rhs.first,lhs.second+rhs.second);}

pair<ll,ll> query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return make_pair(t[x].s,t[x].S);
	int mid=(l+r)>>1;pushdown(x,l,r);
	pair<ll,ll> ret=make_pair(0,0);
	if(ql<=mid) ret=ret+query(x<<1,l,mid,ql,qr);
	if(qr>mid)  ret=ret+query(x<<1|1,mid+1,r,ql,qr);
	return ret;
}

int main()
{
	scanf("%d%*d",&n);
	for(int i=1,x;i<=n;i++)  scanf("%d",&x),v[x].push_back(i);
	for(int i=0,L,R,S;i<n;i++)
	{
		if(!v[i].size()) continue;
		S=0;L=1;
		t[1].cls=1;t[1].s=t[1].S=t[1].tag=0;
		change(1,-n,n,0,0,1);
		if(v[i][0]==1) ++Ans,++S,change(1,-n,n,S,S,1),L=2;
		for(int p:v[i])
		{
			if(p==1) continue;
			R=p-1;
			if(R-L+1>0)
			{
				pair<ll,ll> tmp=query(1,-n,n,S-(R-L+1),S-1);
				Ans+=(S-1)*tmp.first-tmp.second;
				tmp=query(1,-n,n,-n,S-(R-L+1)-1);
				Ans+=(R-L+1)*tmp.first;change(1,-n,n,S-(R-L+1),S-1,1);
				S-=(R-L+1);
			}
			++S;
			Ans+=query(1,-n,n,-n,S-1).first;
			change(1,-n,n,S,S,1);
			L=p+1;
		}
		R=n;
		if(R-L+1>0)
		{
			pair<ll,ll> tmp=query(1,-n,n,S-(R-L+1)-1,S-1);
			Ans+=(S-1)*tmp.first-tmp.second;
			tmp=query(1,-n,n,-n,S-(R-L+1)-2);
			Ans+=(R-L+1)*tmp.first;change(1,-n,n,S-(R-L+1),S-1,1);
			S-=(R-L+1);
		}
	}
	printf("%lld\n",Ans);
}