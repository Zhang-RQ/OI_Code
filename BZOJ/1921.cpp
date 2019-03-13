#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int LIM=230;

struct Suffix_Automaton{
	int son[MAXN][26],trans[MAXN][26],s[MAXN],rig[MAXN];
	int mx[MAXN],par[MAXN],ord[MAXN],tag[MAXN],siz[MAXN],lst,rt,cnt;

	Suffix_Automaton(){lst=rt=cnt=1;}

	void append(int x)
	{
		int p=lst,np=++cnt;
		siz[np]=1;mx[np]=mx[p]+1;
		s[mx[np]]=x;rig[np]=mx[np];
		while(p&&!son[p][x]) son[p][x]=np,p=par[p];
		if(!p) par[np]=rt;
		else
		{
			int q=son[p][x];
			if(mx[q]==mx[p]+1) par[np]=q;
			else
			{
				int nq=++cnt;
				mx[nq]=mx[p]+1;
				par[nq]=par[q];
				par[q]=par[np]=nq;
				memcpy(son[nq],son[q],sizeof son[q]);
				while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
			}
		}
		lst=np;
	}

	void topo()
	{
		static int buk[MAXN];
		memset(buk,0,sizeof buk);
		int Mx=0;
		for(int i=1;i<=cnt;i++)
			buk[mx[i]]++,Mx=max(Mx,mx[i]);
		for(int i=1;i<=Mx;i++)
			buk[i]+=buk[i-1];
		for(int i=1;i<=cnt;i++)
			ord[buk[mx[i]]--]=i;
		for(int i=cnt;i>1;i--)
		{
			int p=ord[i];
			if(!rig[par[p]]) rig[par[p]]=rig[p];
			trans[par[p]][s[rig[p]-mx[par[p]]]]=p;
			siz[par[p]]+=siz[p];
		}
	}

	void push()
	{
		for(int i=2;i<=cnt;i++)
			tag[ord[i]]+=tag[par[ord[i]]];
	}
}SAM,SAMr;

char str[MAXN];
int vis[MAXN],c[MAXN],siz[MAXN],mx_rt,rt;
int pos[MAXN],posr[MAXN],n,m,stk[MAXN],top;
vector<int> T[MAXN];
ll Ans;

void get_rt(int x,int fa,int sz)
{
	siz[x]=1;
	int mx=1;
	for(int v:T[x])
	{
		if(v==fa||vis[v]) continue;
		get_rt(v,x,sz);
		siz[x]+=siz[v];
		mx=max(mx,siz[v]);
	}
	mx=max(mx,sz-siz[x]);
	if(mx<mx_rt) rt=x,mx_rt=mx;
}

void dfs1(int x,int fa,int cur,int f)
{
	if(!SAM.son[cur][c[x]]) return;
	cur=SAM.son[cur][c[x]];
	Ans+=f*SAM.siz[cur];
	for(int v:T[x])
		if(!vis[v]&&v!=fa)
			dfs1(v,x,cur,f);
}

void dfs2(int x,int fa)
{
	dfs1(x,0,SAM.rt,1);
	for(int v:T[x])
		if(v!=fa&&!vis[v])
			dfs2(v,x);
}

void put_vis(int x,int fa)
{
	for(int v:T[x])
		if(v!=fa&&!vis[v])
			put_vis(v,x);
	vis[x]=1;
}

void dfs3(int x,int fa,int nxt)
{
	stk[++top]=c[x];
	int p=SAM.rt;
	for(int i=top;i;i--)
		p=SAM.son[p][stk[i]];
	if(p) dfs1(nxt,0,p,-1);
	for(int v:T[x])
		if(v!=fa&&!vis[v])
			dfs3(v,x,nxt);
	--top;
}

void dfs5(int x,int fa,int len,int cur,Suffix_Automaton &S)
{
	if(len==S.mx[cur]) cur=S.trans[cur][c[x]];
	else if(S.s[S.rig[cur]-len]!=c[x]) cur=0;
	if(!cur) return;
	S.tag[cur]++;
	for(int v:T[x])
		if(v!=fa&&!vis[v])
			dfs5(v,x,len+1,cur,S);
}

void solve_huge(int x,int ofs,int f)
{
	memset(SAM.tag,0,sizeof SAM.tag);
	memset(SAMr.tag,0,sizeof SAMr.tag);
	if(ofs==-1) dfs5(x,0,0,SAM.rt,SAM),dfs5(x,0,0,SAMr.rt,SAMr);
	else
	{
		int cur1=SAM.trans[SAM.rt][ofs],cur2=SAMr.trans[SAMr.rt][ofs];
		if(cur1) dfs5(x,0,1,cur1,SAM);
		if(cur2) dfs5(x,0,1,cur2,SAMr);
	}
	SAM.push();SAMr.push();
	for(int i=1;i<=m;i++)
		Ans+=1ll*f*SAM.tag[pos[i]]*SAMr.tag[posr[i]];
}

void solve(int x,int sz)
{
	if(sz<=LIM)	dfs2(x,0),put_vis(x,0);
	else
	{
		vis[x]=1;
		solve_huge(x,-1,1);
		for(int v:T[x])
			if(!vis[v])
			{
				int szv=siz[v]<siz[x]?siz[v]:sz-siz[x];
				if(szv<=LIM) stk[top=1]=c[x],dfs3(v,0,v);
				else solve_huge(v,c[x],-1);
			}
		for(int v:T[x])
			if(!vis[v])
			{
				int szv=siz[v]<siz[x]?siz[v]:sz-siz[x];
				mx_rt=1<<30;
				get_rt(v,0,szv);
				solve(v,szv);
			}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),T[u].push_back(v),T[v].push_back(u);
	scanf("%s",str+1);
	for(int i=1;i<=n;i++)
		c[i]=str[i]-'a';
	scanf("%s",str+1);
	for(int i=1;i<=m;i++)
		SAM.append(str[i]-'a'),pos[i]=SAM.lst;
	for(int i=m;i;i--)
		SAMr.append(str[i]-'a'),posr[i]=SAMr.lst;
	SAM.topo();SAMr.topo();
	mx_rt=1<<30;
	get_rt(1,0,n);
	solve(rt,n);
	printf("%lld\n",Ans);
}
