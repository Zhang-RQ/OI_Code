#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

struct node_t{int l,r,s;}t[MAXN*80];

int n,m,q,jmp[MAXN][20],dep[MAXN],DEP[MAXN],JMP[MAXN][20],cnt,rt[MAXN],tot,pnt[MAXN],siz[MAXN];
ll pre[MAXN],rDEP[MAXN],pt[MAXN];
vector<int> T[MAXN];

void insert(int &x,int l,int r,int p)
{
	if(!x) x=++cnt;
	t[x].s++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p);
	else insert(t[x].r,mid+1,r,p);
}

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	int z=++cnt;
	t[z].s=t[x].s+t[y].s;
	t[z].l=merge(t[x].l,t[y].l);
	t[z].r=merge(t[x].r,t[y].r);
	return z;
}

int Kth(int x,int l,int r,int k)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(t[t[x].l].s<k)
		return Kth(t[x].r,mid+1,r,k-t[t[x].l].s);
	else
		return Kth(t[x].l,l,mid,k);
}

void dfs(int x,int fa)
{
	siz[x]=1;
	insert(rt[x],1,n,x);
	jmp[x][0]=fa;
	dep[x]=dep[fa]+1;
	for(int v:T[x])
		if(v!=fa)
			dfs(v,x),siz[x]+=siz[v],
			rt[x]=merge(rt[x],rt[v]);
}

int LCA1(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int j=19;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			x=jmp[x][j];
	if(x==y) return x;
	for(int j=19;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

int LCA2(int x,int y)
{
	if(DEP[x]<DEP[y])
		swap(x,y);
	for(int j=19;~j;j--)
		if(DEP[JMP[x][j]]>=DEP[y])
			x=JMP[x][j];
	if(x==y) return x;
	for(int j=19;~j;j--)
		if(JMP[x][j]!=JMP[y][j])
			x=JMP[x][j],y=JMP[y][j];
	return JMP[x][0];
}

int NXT(int x,int y)
{
	for(int j=19;~j;j--)
		if(DEP[JMP[x][j]]>DEP[y])
			x=JMP[x][j];
	return x;
}

int getid(ll p){return lower_bound(pre+1,pre+1+tot,p)-pre;}

int getrid(ll p)
{
	int x=getid(p);
	return Kth(rt[pnt[x]],1,n,p-pre[x-1]);
}

ll getDEP(ll p)
{
	int x=getid(p);
	return rDEP[x]+dep[Kth(rt[pnt[x]],1,n,p-pre[x-1])]-dep[pnt[x]];
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		T[u].push_back(v),
		T[v].push_back(u);
	dfs(1,0);
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	pre[tot=1]=n;DEP[1]=rDEP[1]=1;pnt[1]=1;
	ll x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		int fa=getid(y);
		++tot;
		JMP[tot][0]=fa;pt[tot]=y;
		pnt[tot]=x;pre[tot]=pre[tot-1]+siz[x];
		DEP[tot]=DEP[fa]+1;
		rDEP[tot]=rDEP[fa]+dep[Kth(rt[pnt[fa]],1,n,y-pre[fa-1])]-dep[pnt[fa]]+1;
	}
	for(int j=1;j<=19;j++)
		for(int i=1;i<=tot;i++)
			JMP[i][j]=JMP[JMP[i][j-1]][j-1];
	for(int i=1;i<=q;i++)
	{
		scanf("%lld%lld",&x,&y);
		int u=getid(x),v=getid(y);
		int LCA=LCA2(u,v);
		ll a=pt[NXT(u,LCA)],b=pt[NXT(v,LCA)];
		if(u==LCA) a=x;
		if(v==LCA) b=y;
		int rLCA=LCA1(getrid(a),getrid(b));
		printf("%lld\n",getDEP(x)+getDEP(y)-2*(rDEP[LCA]+dep[rLCA]-dep[pnt[LCA]]));
	}
}
