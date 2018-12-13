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
const int INF=1E9;

struct node{
	int l,r,s;
}t[MAXN<<6];

int rt[MAXN],cnt,n,m;

void insert(int &x,int l,int r,int p,int y)
{
	x=++cnt;
	t[x]=t[y];
	t[x].s+=p;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p,t[y].l);
	else insert(t[x].r,mid+1,r,p,t[y].r);
}

int query(int x,int l,int r,int ql,int qr,int y)
{
	if(ql<=l&&r<=qr) return t[x].s-t[y].s;
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr,t[y].l);
	else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr,t[y].r);
	else return query(t[x].l,l,mid,ql,qr,t[y].l)+query(t[x].r,mid+1,r,ql,qr,t[y].r);
}

int solve(int l,int r)
{
	int ret=query(rt[r],1,INF,1,1,rt[l-1]);
	if(!ret) return 1;
	while(1)
	{
		int _ret=ret;
		ret=query(rt[r],1,INF,1,ret+1,rt[l-1]);
		if(ret==_ret) break;
	}
	return ret+1;
}

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),insert(rt[i],1,INF,x,rt[i-1]);
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r),printf("%d\n",solve(l,r));
}