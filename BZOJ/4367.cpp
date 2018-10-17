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

struct node{
	int l,r,v;
	ll s;
}t[(MAXN<<4)+(MAXN<<3)];

int n,a[MAXN],rt[MAXN],cnt,v[MAXN],Mx,st,d;
ll f[MAXN*2],g[MAXN*2],f1[MAXN*2],g1[MAXN*2],Ans;

void insert(int &x,int l,int r,int p,int y)
{
	x=++cnt;
	t[x]=t[y];
	t[x].v++;t[x].s+=v[p];
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p,t[y].l);
	else insert(t[x].r,mid+1,r,p,t[y].r);
}

ll query(int x,int l,int r,int k,int y)
{
	if(k<=0) return 0;
	if(k>=t[x].v) return t[x].s-t[y].s;
	if(l==r) return 1ll*v[l]*min(k,t[x].v-t[y].v);
	int mid=(l+r)>>1,rsiz=t[t[x].r].v-t[t[y].r].v;
	if(k<=rsiz) return query(t[x].r,mid+1,r,k,t[y].r);
	else return query(t[x].l,l,mid,k-rsiz,t[y].l)+t[t[x].r].s-t[t[y].r].s;
}

void solve1(int l,int r,int L,int R) //[l,r] statu,[L,R] desicion
{
	if(l>r) return;
	int mid=(l+r)>>1,pos=0;
	ll Ans=-(1ll<<60);
	for(int i=L;i<=R;i++)
	{
		ll tAns=query(rt[i],1,Mx,mid-i+st,rt[st-1]);
		if(tAns>Ans) Ans=tAns,pos=i; 
	}
	f[mid]=Ans;
	solve1(l,mid-1,L,pos);solve1(mid+1,r,pos,R);
}

void solve2(int l,int r,int L,int R) //[l,r] statu,[L,R] desicion
{
	if(l>r) return;
	int mid=(l+r)>>1,pos=0;
	ll Ans=-(1ll<<60);
	for(int i=L;i<=R;i++)
	{
		ll tAns=query(rt[st-1],1,Mx,mid+i-st,rt[i-1]);
		if(tAns>Ans) Ans=tAns,pos=i; 
	}
	g[mid]=Ans;
	solve2(l,mid-1,pos,R);solve2(mid+1,r,L,pos);
}

void solve3(int l,int r,int L,int R) //[l,r] statu,[L,R] desicion
{
	if(l>r) return;
	int mid=(l+r)>>1,pos=0;
	ll Ans=-(1ll<<60);
	for(int i=L;i<=R;i++)
	{
		ll tAns=query(rt[i],1,Mx,mid-((i-st)<<1),rt[st-1]);
		if(tAns>Ans) Ans=tAns,pos=i; 
	}
	f1[mid]=Ans;
	solve3(l,mid-1,L,pos);solve3(mid+1,r,pos,R);
}

void solve4(int l,int r,int L,int R) //[l,r] statu,[L,R] desicion
{
	if(l>r) return;
	int mid=(l+r)>>1,pos=0;
	ll Ans=-(1ll<<60);
	for(int i=L;i<=R;i++)
	{
		ll tAns=query(rt[st-1],1,Mx,mid-((st-i)<<1),rt[i-1]);
		if(tAns>Ans) Ans=tAns,pos=i; 
	}
	g1[mid]=Ans;
	solve4(l,mid-1,pos,R);solve4(mid+1,r,L,pos);
}

int main()
{
	scanf("%d%d%d",&n,&st,&d);++st;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),v[i]=a[i];
	sort(v+1,v+1+n);
	Mx=unique(v+1,v+1+n)-v-1;
	for(int i=1;i<=n;i++)
	{
		a[i]=lower_bound(v+1,v+1+Mx,a[i])-v;
		insert(rt[i],1,Mx,a[i],rt[i-1]);
	}
	solve1(1,min(d,200010),st,min(st+d,n));
	solve2(1,min(d,200010),max(1,st-d),st);
	solve3(1,min(d,200010),st,min(st+(d>>1),n));
	solve4(1,min(d,200010),max(1,st-(d>>1)),st);
	for(int i=0;i<=min(d,200010);i++)
		if(d-i<=200010)
			Ans=max(Ans,max(f1[i]+g[d-i],g1[i]+f[d-i]));
	for(int i=0;i<=min(d,200010);i++)
		if(d-i<=200010)
			Ans=max(Ans,max(f1[d-i]+g[i],g1[d-i]+f[i]));
	printf("%lld\n",Ans);
}