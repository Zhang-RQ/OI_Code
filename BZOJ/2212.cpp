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

int n,ls[MAXN<<1],rs[MAXN<<1],cnt,tot,rt[MAXN<<1],Rt;
ll S1,S2,Ans;

struct node{
	int l,r,siz;
}t[MAXN<<7];

void insert(int &x,int l,int r,int pos)
{
	x=++cnt;
	t[x].siz++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) insert(t[x].l,l,mid,pos);
	else insert(t[x].r,mid+1,r,pos);
}

void read(int &x)
{
	static int v;
	x=++tot;scanf("%d",&v);
	if(v) insert(rt[x],1,n,v);
	else read(ls[x]),read(rs[x]);
}

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	int z=++cnt;
	t[z].l=merge(t[x].l,t[y].l);
	t[z].r=merge(t[x].r,t[y].r);
	t[z].siz=t[x].siz+t[y].siz;
	S1+=1ll*t[t[x].l].siz*t[t[y].r].siz;
	S2+=1ll*t[t[x].r].siz*t[t[y].l].siz;
	return z;
}

void solve(int x)
{
	if(!ls[x]) return;
	solve(ls[x]),solve(rs[x]);
	S1=S2=0;
	rt[x]=merge(rt[ls[x]],rt[rs[x]]); //notice
	Ans+=min(S1,S2);
}

int main()
{
	scanf("%d",&n);read(Rt);
	solve(Rt);
	printf("%lld\n",Ans);
}