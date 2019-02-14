#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXM=5E5+10;

ll Ans[MAXM],tAns;
vector<int> g[MAXN];
int n,m,jmp[MAXN][20],dft,dep[MAXN],blksiz,Rt=1;
int pos[MAXN],siz[MAXN],a[MAXN],v[MAXN],t[MAXN],tot,cnt1[MAXN],cnt2[MAXN],totq;
pair<int,int> p1[5],p2[5];

struct Que{
	int x,y,f,id;

	bool operator < (const Que &rhs) const {return (x/blksiz<rhs.x/blksiz)||(x/blksiz==rhs.x/blksiz&&y<rhs.y);}
}Q[MAXM<<4];

void Ins1(int x) {tAns+=cnt2[t[x]],cnt1[t[x]]++;}

void Era1(int x) {tAns-=cnt2[t[x]],cnt1[t[x]]--;}

void Ins2(int x) {tAns+=cnt1[t[x]],cnt2[t[x]]++;}

void Era2(int x) {tAns-=cnt1[t[x]],cnt2[t[x]]--;}

void Add_Q(int l1,int r1,int l2,int r2,int id)
{
	l1=max(l1,1);l2=max(l2,1);
	r1=min(r1,n);r2=min(r2,n);
	if(l1>r1||l2>r2) return;
	Q[++tot]=(Que){r1,r2,1,id};
	if(l1) Q[++tot]=(Que){l1-1,r2,-1,id};
	if(l2) Q[++tot]=(Que){r1,l2-1,-1,id};
	if(l1&&l2) Q[++tot]=(Que){l1-1,l2-1,1,id};
}

void dfs(int x,int fa)
{
	siz[x]=1;pos[x]=++dft;
	jmp[x][0]=fa;dep[x]=dep[fa]+1;
	for(int v:g[x])
		if(v!=fa)
			dfs(v,x),siz[x]+=siz[v];
}

void init()
{
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
}

int Nxt(int x,int y)
{
	for(int j=19;~j;j--)
		if(dep[jmp[x][j]]>dep[y])
			x=jmp[x][j];
	return x;
}

int main()
{
	scanf("%d%d",&n,&m);blksiz=sqrt(n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[i]=a[i];
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
	dfs(1,0);init();
	sort(v+1,v+1+n);
	int totv=unique(v+1,v+1+n)-v-1;
	for(int i=1;i<=n;i++) t[pos[i]]=lower_bound(v+1,v+1+totv,a[i])-v;
	for(int i=1,opt,x,y,tot1=0,tot2=0;i<=m;i++)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1) Rt=x;
		else
		{
			scanf("%d",&y);
			tot1=tot2=0;
			if(x==Rt) p1[tot1=1]={1,n};
			else if(pos[x]<=pos[Rt]&&pos[Rt]<=pos[x]+siz[x]-1)
			{
				tot1=2;
				int p=Nxt(Rt,x);
				p1[1]={1,pos[p]-1};
				p1[2]={pos[p]+siz[p],n};
			}
			else p1[tot1=1]={pos[x],pos[x]+siz[x]-1};
			if(y==Rt) p2[tot2=1]={1,n};
			else if(pos[y]<=pos[Rt]&&pos[Rt]<=pos[y]+siz[y]-1)
			{
				tot2=2;
				int p=Nxt(Rt,y);
				p2[1]={1,pos[p]-1};
				p2[2]={pos[p]+siz[p],n};
			}
			else p2[tot2=1]={pos[y],pos[y]+siz[y]-1};
			++totq;
			for(int j=1;j<=tot1;j++)
				for(int k=1;k<=tot2;k++)
					Add_Q(p1[j].first,p1[j].second,p2[k].first,p2[k].second,totq);
		}
	}
	sort(Q+1,Q+1+tot);
	int ptr1=0,ptr2=0;
	for(int i=1;i<=tot;i++)
	{
		while(ptr1<Q[i].x) Ins1(++ptr1);
		while(ptr1>Q[i].x) Era1(ptr1--);
		while(ptr2<Q[i].y) Ins2(++ptr2);
		while(ptr2>Q[i].y) Era2(ptr2--);
		Ans[Q[i].id]+=Q[i].f*tAns;
	}
	for(int i=1;i<=totq;i++) printf("%lld\n",Ans[i]);
}