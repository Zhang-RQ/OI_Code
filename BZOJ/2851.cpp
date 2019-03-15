#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

struct edge_t{
	int v,nxt;
}Edge[MAXN<<1];

int n,q,rt,dis[MAXN],head[MAXN],cnt_e,Pnt[MAXN],tot;
int dep[MAXN],jmp[MAXN][19],pos[MAXN],dft;

bool cmp(int x,int y){return pos[x]<pos[y];}

void add(int u,int v)
{
	Edge[++cnt_e]=(edge_t){v,head[u]};
	head[u]=cnt_e;
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int j=18;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			x=jmp[x][j];
	if(x==y) return x;
	for(int j=18;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

void dfs(int x)
{
	pos[x]=++dft;
	for(int _=head[x];_;_=Edge[_].nxt)
		dfs(Edge[_].v);
}

int main()
{
	scanf("%d",&n);
	rt=n+1;dep[rt]=1;dis[rt]=0;
	for(int i=1;i<=n;i++)
	{
		int cnt,lst=-1,x;
		scanf("%d",&cnt);
		while(cnt--)
		{
			scanf("%d",&x);
			if(~lst) lst=LCA(lst,x);
			else lst=x;
		}
		if(~lst) jmp[i][0]=lst;
		else jmp[i][0]=rt;
		add(jmp[i][0],i);
		dep[i]=dep[jmp[i][0]]+1;
		dis[i]=dis[jmp[i][0]]+1;
		for(int j=1;j<=18;j++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	}
	dfs(rt);
	scanf("%d",&q);
	for(int _=1;_<=q;_++)
	{
		scanf("%d",&tot);
		for(int i=1;i<=tot;i++)
			scanf("%d",&Pnt[i]);
		sort(Pnt+1,Pnt+1+tot,cmp);
		tot=unique(Pnt+1,Pnt+1+tot)-Pnt-1;
		int Ans=dis[Pnt[1]];
		for(int i=2;i<=tot;i++)
			Ans+=dis[Pnt[i]],Ans-=dis[LCA(Pnt[i-1],Pnt[i])];
		printf("%d\n",Ans);
	}
}
