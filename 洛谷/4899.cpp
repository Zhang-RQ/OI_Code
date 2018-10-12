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

const int MAXM=4E5+10;

struct __edge{
	int u,v,w;
	__edge(){}
	__edge(int _u,int _v,int _w){u=_u;v=_v;w=_w;}
}E1[MAXM],E2[MAXM];

struct node{
	int l,r,v;
}t[MAXM<<7];

int fa[MAXM],n,m,q,Rt1,Rt2,cnt1,cnt2,val1[MAXM],val2[MAXM],pos1[MAXM],pos2[MAXM],siz1[MAXM],siz2[MAXM];
int cnt,rt[MAXM],jmp1[MAXM][20],jmp2[MAXM][20],dft1,dft2,N,ar[MAXM];
vector<int> T1[MAXM],T2[MAXM];

bool cmp1(const __edge &lhs,const __edge &rhs) {return lhs.w<rhs.w;}

bool cmp2(const __edge &lhs,const __edge &rhs) {return lhs.w>rhs.w;}

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void dfs1(int x,int fa)
{
	jmp1[x][0]=fa;
	siz1[x]=1;pos1[x]=++dft1;
	for(int v:T1[x])
		dfs1(v,x),siz1[x]+=siz1[v];
}

void dfs2(int x,int fa)
{
	jmp2[x][0]=fa;
	siz2[x]=1;pos2[x]=++dft2;
	for(int v:T2[x])
		dfs2(v,x),siz2[x]+=siz2[v];
}

void init()
{
	for(int j=1;j<=19;j++)
		for(int i=1;i<=N;i++)
		{
			jmp1[i][j]=jmp1[jmp1[i][j-1]][j-1];
			jmp2[i][j]=jmp2[jmp2[i][j-1]][j-1];
		}
}

void insert(int &x,int l,int r,int p,int y)
{
	x=++cnt;
	t[x]=t[y];
	t[x].v++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p,t[y].l);
	else insert(t[x].r,mid+1,r,p,t[y].r);
}

int query(int x,int l,int r,int ql,int qr,int y)
{
	if(ql<=l&&r<=qr) return t[x].v-t[y].v;
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr,t[y].l);
	else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr,t[y].r);
	else return query(t[x].l,l,mid,ql,qr,t[y].l)+query(t[x].r,mid+1,r,ql,qr,t[y].r);
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	N=(n<<1)-1;
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		++u;++v;
		E1[i]=__edge(u,v,min(u,v));
		E2[i]=__edge(u,v,max(u,v));
	}
	sort(E1+1,E1+1+m,cmp2);sort(E2+1,E2+1+m,cmp1);
	cnt1=cnt2=n;val2[0]=1<<30;
	for(int i=1;i<=N;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u=find(E1[i].u),v=find(E1[i].v);
		if(u!=v)
		{
			++cnt1;Rt1=cnt1;
			val1[cnt1]=E1[i].w;
			T1[cnt1].push_back(u);
			T1[cnt1].push_back(v);
			fa[u]=cnt1;fa[v]=cnt1;
		}
	}
	for(int i=1;i<=N;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u=find(E2[i].u),v=find(E2[i].v);
		if(u!=v)
		{
			++cnt2;Rt2=cnt2;
			val2[cnt2]=E2[i].w;
			T2[cnt2].push_back(u);
			T2[cnt2].push_back(v);
			fa[u]=cnt2;fa[v]=cnt2;
		}
	}
	dfs1(Rt1,0);dfs2(Rt2,0);init();
	for(int i=1;i<=n;i++)
		ar[pos1[i]]=pos2[i];
	for(int i=1;i<=N;i++)
		insert(rt[i],1,N,ar[i],rt[i-1]);
	for(int i=1,s,t,l,r;i<=q;i++)
	{
		scanf("%d%d%d%d",&s,&t,&l,&r);
		++s,++t;++l;++r;
		for(int j=19;~j;j--)
		{
			if(val1[jmp1[s][j]]>=l)
				s=jmp1[s][j];
			if(val2[jmp2[t][j]]<=r)
				t=jmp2[t][j];
		}
		printf("%d\n",query(rt[pos1[s]+siz1[s]-1],1,N,pos2[t],pos2[t]+siz2[t]-1,rt[pos1[s]-1])?1:0);
	}
}