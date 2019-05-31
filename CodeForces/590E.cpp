#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=760;
const int MAXL=1E7+10;

bool vis[MAXN],tag[MAXN<<1];
char Pool[MAXL<<1],*s[MAXN],*cur=Pool;
int son[MAXL][2],fail[MAXL],rt,cnt,jmp[MAXL],ed[MAXL],n,mat[MAXN],matr[MAXN];
bitset<MAXN> G[MAXN];
vector<int> g[MAXN],g2[MAXN];

void insert(char *s,int id)
{
	int x=rt;
	for(int i=1;s[i];i++)
	{
		if(!son[x][s[i]-'a'])
			son[x][s[i]-'a']=++cnt;
		x=son[x][s[i]-'a'];
	}
	ed[x]=id;
}

void build()
{
	queue<int> q;
	for(int i=0;i<2;i++)
		if(son[rt][i])
			q.push(son[rt][i]);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		jmp[x]=ed[x]?ed[x]:jmp[fail[x]];
		for(int i=0;i<2;i++)
			if(son[x][i])
				fail[son[x][i]]=son[fail[x]][i],
				q.push(son[x][i]);
			else
				son[x][i]=son[fail[x]][i];
	}
}

bool match(int x)
{
	for(int v:g[x])
		if(!vis[v])
		{
			vis[v]=1;
			if(!mat[v]||match(mat[v]))
				return mat[v]=x,true;
		}
	return false;
}

void dfs(int x,int tp)//tp=0 left,tp=1 right
{
	if(tp==0)
	{
		tag[x]=1;
		if(!tag[matr[x]+n])
			dfs(matr[x],1);
	}
	else
	{
		tag[x+n]=1;
		for(int v:g2[x])
			if(v!=mat[x]&&!tag[v])
				dfs(v,0);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		s[i]=cur;
		scanf("%s",s[i]+1);
		cur+=strlen(s[i]+1)+10;
		insert(s[i],i);
	}
	build();
	for(int i=1;i<=n;i++)
	{
		int x=rt,p;
		for(int j=1;s[i][j];j++)
		{
			x=son[x][s[i][j]-'a'],p=ed[x]==i?fail[x]:x;
			if(jmp[p])
				G[i][jmp[p]]=1;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(G[i][j])
				G[i]|=G[j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(G[i][j]&&i!=j)
				g[i].push_back(j),
				g2[j].push_back(i);
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof vis);
		match(i);
	}
	for(int i=1;i<=n;i++)
		if(mat[i])
			matr[mat[i]]=i;
	for(int i=1;i<=n;i++)
		if(!mat[i])
			dfs(i,1);
	int Ans=0;
	for(int i=1;i<=n;i++)
		if(!tag[i]&&tag[i+n])
			++Ans;
	printf("%d\n",Ans);
	for(int i=1;i<=n;i++)
		if(!tag[i]&&tag[i+n])
			printf("%d ",i);
	puts("");
}
