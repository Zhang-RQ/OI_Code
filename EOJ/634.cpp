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

const int MAXN=3E5+10;
const int P=1E9+7;

int n,c[MAXN],visc[MAXN];
vector<int> T[MAXN];

struct dat{
	ll a,b,c,d;

	dat(ll _a=1,ll _b=0,ll _c=0,ll _d=0){a=_a;b=_b;c=_c;d=_d;}

	dat operator * (const dat &rhs) const {return dat(a*rhs.a%P,(rhs.a*b+rhs.b)%P,(c+rhs.c*a)%P,(d+rhs.d+rhs.c*b)%P);}
	dat& operator *= (const dat &rhs) {return (*this)=(*this)*rhs;}
};

struct node_t{
	int l,r;
	dat v;
}t[MAXN*30];

int cnt,rt[MAXN],cntpnt;
ll Ans;
int stk[MAXN*5],top;
set<int> s[MAXN];

int newnode()
{
	assert(cnt<MAXN*30);
	if(!top) return ++cnt;
	int x=stk[top--];
	if(t[x].l) stk[++top]=t[x].l,t[x].l=0;
	if(t[x].r) stk[++top]=t[x].r,t[x].r=0;
	t[x].v=dat(1,0,0,0);
	return x;
}

void pushdown(int x)
{
	if(!t[x].l) t[x].l=newnode();
	if(!t[x].r) t[x].r=newnode();
	t[t[x].l].v*=t[x].v;
	t[t[x].r].v*=t[x].v;
	t[x].v=dat(1,0,0,0);
}

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	if(!t[x].l&&!t[x].r) return t[y].v*=dat(t[x].v.b,0,0,t[x].v.d),stk[++top]=x,y;
	if(!t[y].l&&!t[y].r) return t[x].v*=dat(t[y].v.b,0,0,t[y].v.d),stk[++top]=y,x;
	pushdown(x);pushdown(y);
	t[x].l=merge(t[x].l,t[y].l);
	t[x].r=merge(t[x].r,t[y].r);
	return x;
}

void change(int x,int l,int r,int cl,int cr,const dat &rhs)
{
	if(cl<=l&&r<=cr) return t[x].v*=rhs,void();
	int mid=(l+r)>>1;pushdown(x);
	if(cl<=mid) change(t[x].l,l,mid,cl,cr,rhs);
	if(cr>mid)  change(t[x].r,mid+1,r,cl,cr,rhs);
}

dat queryf(int x,int l,int r,int p)
{
	if(l==r) return t[x].v;
	if(!t[x].l&&!t[x].r) return t[x].v;
	int mid=(l+r)>>1;
	if(p<=mid) return queryf(t[x].l,l,mid,p)*t[x].v;
	else return queryf(t[x].r,mid+1,r,p)*t[x].v;
}

void dfs_seg(int x,int l,int r)
{
	if(l==r) return (Ans+=t[x].v.d)%=P,void();
	if(!t[x].l&&!t[x].r)	return (Ans+=t[x].v.d*(r-l+1))%=P,void();
	int mid=(l+r)>>1;pushdown(x);
	dfs_seg(t[x].l,l,mid);dfs_seg(t[x].r,mid+1,r);
}

void dfs(int x)
{
	rt[x]=++cnt;
	change(rt[x],1,n,1,n,dat(0,1,0,0));
	for(int v:T[x])
	{
		dfs(v);
		if(c[x]==c[v]) change(rt[v],1,n,1,n,dat(1,1,0,0)),rt[x]=merge(rt[x],rt[v]);
		else
		{
			ll tmp=queryf(rt[v],1,n,c[x]).b;
			change(rt[x],1,n,c[v],c[v],dat(tmp+1,0,0,0));
			change(rt[v],1,n,1,n,dat(0,1,0,0));
			rt[x]=merge(rt[x],rt[v]);
		}
	}
	change(rt[x],1,n,1,n,dat(1,0,1,0));
	Ans=(Ans-(n-1)*queryf(rt[x],1,n,c[x]).b%P+P)%P;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=2,fa;i<=n;i++) scanf("%d",&fa),T[fa].push_back(i);
	dfs(1);
	dfs_seg(rt[1],1,n);
	printf("%lld\n",Ans);
}
