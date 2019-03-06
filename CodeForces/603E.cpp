#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXM=3E5+10;

struct edge_t{
	int u,v,w,id;

	bool operator < (const edge_t &rhs) const {return w<rhs.w;}
}e1[MAXM],e2[MAXM];

struct opt{
	int x,y,sizx,sizy;
}stk[MAXN];

int n,m,siz[MAXN],fa[MAXN],tot,top,Ans[MAXM],gpos[MAXM];

int find(int x) {return x==fa[x]?x:find(fa[x]);}

void undo()
{
	int x=stk[top].x,y=stk[top].y,sizx=stk[top].sizx,sizy=stk[top].sizy;
	if(fa[x]==x) tot-=siz[x]&1;
	else tot-=siz[y]&1;
	fa[x]=x;fa[y]=y;
	siz[x]=sizx;siz[y]=sizy;
	tot+=siz[x]&1;tot+=siz[y]&1;
	--top;
}

void merge(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	if(siz[x]<siz[y]) swap(x,y);
	stk[++top]=(opt){x,y,siz[x],siz[y]};
	tot-=siz[x]&1;tot-=siz[y]&1;
	fa[y]=x;siz[x]+=siz[y];
	tot+=siz[x]&1;
}

void solve(int l,int r,int vl,int vr)
{
	if(l>r||vl>vr) return;
	int mid=(l+r)>>1;
	int top1=top,pos=0;
	for(int i=l;i<=mid;i++)
		if(gpos[i]<vl)
			merge(e1[i].u,e1[i].v);
	int top2=top;
	for(int i=vl;i<=vr;i++)
		if(e2[i].id<=mid)
		{
			merge(e2[i].u,e2[i].v);
			if(!tot) {pos=i;break;}
		}
	if(!pos)
	{
		for(int i=l;i<=mid;i++)
			Ans[i]=-1;
		while(top>top2) undo();
		solve(mid+1,r,vl,vr);
		while(top>top1) undo();
		return;
	}
	Ans[mid]=e2[pos].w;
	while(top>top2) undo();
	solve(mid+1,r,vl,pos);
	while(top>top1) undo();
	for(int i=vl;i<pos;i++)
		if(e2[i].id<l)
			merge(e2[i].u,e2[i].v);
	solve(l,mid-1,pos,vr);
	while(top>top1) undo();
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		fa[i]=i,siz[i]=1,++tot;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e1[i].u,&e1[i].v,&e1[i].w),e1[i].id=i,e2[i]=e1[i];
	sort(e2+1,e2+1+m);
	for(int i=1;i<=m;i++) gpos[e2[i].id]=i;
	solve(1,m,1,m);
	for(int i=1;i<=m;i++)
		printf("%d\n",Ans[i]);
}
