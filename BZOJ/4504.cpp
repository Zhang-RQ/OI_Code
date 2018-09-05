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

struct __node{
	ll add,mx;
	int l,r,pos;
}t[MAXN<<7];

struct dat{
	int x,L,R,pos;
	ll val;
	dat(){}
	dat(int _x,int _L,int _R,int _pos,ll _val){x=_x;L=_L;R=_R;pos=_pos;val=_val;}
	inline bool operator < (const dat &rhs) const
	{
		return val<rhs.val;
	}
};

priority_queue<dat> pq;

ll Ans;
map<int,int> pre;
int cnt,n,k,rt[MAXN];

inline void pushup(const int &x)
{
	if(t[t[x].l].mx+t[t[x].l].add>t[t[x].r].mx+t[t[x].r].add)
	{
		t[x].mx=t[t[x].l].mx+t[t[x].l].add;
		t[x].pos=t[t[x].l].pos;
	}
	else
	{
		t[x].mx=t[t[x].r].mx+t[t[x].r].add;
		t[x].pos=t[t[x].r].pos;
	}
}

void build(int &x,int l,int r)
{
	x=++cnt;
	if(l==r) return t[x].pos=l,void();
	int mid=(l+r)>>1;
	build(t[x].l,l,mid);build(t[x].r,mid+1,r);
	pushup(x);
}

void change(int &x,int l,int r,int cl,int cr,int val,int _x)
{
	x=++cnt;t[x]=t[_x];
	if(cl<=l&&r<=cr) return t[x].add+=val,void();
	int mid=(l+r)>>1;
	if(cl<=mid) change(t[x].l,l,mid,cl,cr,val,t[_x].l);
	if(cr>mid)  change(t[x].r,mid+1,r,cl,cr,val,t[_x].r);
	pushup(x);
}

pair<ll,int> query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return make_pair(t[x].mx+t[x].add,t[x].pos);
	int mid=(l+r)>>1;
	if(qr<=mid)
	{
		pair<ll,int> ret=query(t[x].l,l,mid,ql,qr);ret.first+=t[x].add;
		return ret;
	}
	else if(ql>mid)
	{
		pair<ll,int> ret=query(t[x].r,mid+1,r,ql,qr);ret.first+=t[x].add;
		return ret;
	}
	else
	{
		pair<ll,int> ret1=query(t[x].l,l,mid,ql,qr);
		pair<ll,int> ret2=query(t[x].r,mid+1,r,ql,qr);
		ret1.first+=t[x].add;ret2.first+=t[x].add;
		return max(ret1,ret2);
	}
}

int main()
{
	scanf("%d%d",&n,&k);
	build(rt[0],1,n);
	pair<ll,int> p;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		change(rt[i],1,n,pre[x]+1,i,x,rt[i-1]);
		p=query(rt[i],1,n,1,i);
		pq.push(dat(rt[i],1,i,p.second,p.first));
		pre[x]=i;
	}
	while(k--)
	{
		dat t=pq.top();pq.pop();
		Ans=t.val;
		if(t.L<=t.pos-1)
		{
			p=query(t.x,1,n,t.L,t.pos-1);
			pq.push(dat(t.x,t.L,t.pos-1,p.second,p.first));
		}
		if(t.pos+1<=t.R)
		{
			p=query(t.x,1,n,t.pos+1,t.R);
			pq.push(dat(t.x,t.pos+1,t.R,p.second,p.first));
		}
	}
	printf("%lld\n",Ans);
}