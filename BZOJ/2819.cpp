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
const int MAXM=1E6+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,cnt;
int n,pos[MAXN],siz[MAXN],f[MAXN],val[MAXN],rev[MAXN],q,jmp[MAXN][20],dep[MAXN];
int t[MAXN<<3],tg[MAXN<<3];
char str[10];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

inline void pushup(int x){t[x]=t[x<<1]^t[x<<1|1];}

inline void pushdown(int x,int l,int r)
{
	if(tg[x])
	{
		int mid=(l+r)>>1;
		tg[x<<1]^=tg[x];tg[x<<1|1]^=tg[x];
		t[x<<1]^=(mid-l+1)&1?tg[x]:0;
		t[x<<1|1]^=(r-mid)&1?tg[x]:0;
		tg[x]=0;
	}
}

void build(int x,int l,int r)
{
	if(l==r) return t[x]=f[rev[l]],void();
 	int mid=(l+r)>>1;
 	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
 	pushup(x);
}

void change(int x,int l,int r,int cl,int cr,int val)
{
	if(cl<=l&&r<=cr) return tg[x]^=val,t[x]^=(r-l+1)&1?val:0,void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
	if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
	pushup(x);
}

int query(int x,int l,int r,int pos)
{
	if(l==r) return t[x];
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(pos<=mid) return query(x<<1,l,mid,pos);
	else return query(x<<1|1,mid+1,r,pos);
}

void dfs(int x,int fa)
{
	pos[x]=++cnt;siz[x]=1;f[x]=f[fa]^val[x];rev[cnt]=x;
	jmp[x][0]=fa;dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);siz[x]+=siz[v];
	}
}

void init()
{
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;~i;--i)
		if(dep[jmp[x][i]]>=dep[y])
			x=jmp[x][i];
	if(x==y) return x;
	for(int i=19;~i;--i)
		if(jmp[x][i]!=jmp[y][i])
			x=jmp[x][i],y=jmp[y][i];
	return jmp[x][0];
}

int main()
{
	scanf("%d",&n);
	puts("fafa");
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs(1,0);scanf("%d",&q);build(1,1,n);init();
	for(int i=1,x,y;i<=q;i++)
	{
		scanf("%s%d%d",str+1,&x,&y);
		if(str[1]=='Q')	puts(query(1,1,n,pos[x])^query(1,1,n,pos[y])^val[LCA(x,y)]?"Yes":"No");
		else
		{
			y=val[x]^y;val[x]^=y;
			change(1,1,n,pos[x],pos[x]+siz[x]-1,y);
		}
	}
}