#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXS=3E5+10;

struct edge_t{
	int v,c,nxt;
}Edge[MAXN<<1];

struct Qu{int p,id,f;};

int head[MAXN],cnt_e;

void add(int u,int v,int c)
{
	Edge[++cnt_e]=(edge_t){v,c,head[u]};
	head[u]=cnt_e;
}

int Ans[MAXS];
char s[MAXS];
int s1[MAXS],s2[MAXS],stk[MAXS];
int nxt[MAXS],jmp[MAXN][18],dep[MAXN],n,m,fac[MAXN];
vector<Qu> Q1[MAXN],Q2[MAXN];

int Match(int len1,int len2) //find s2 in s1
{
	for(int i=2,j=0;i<=len2;i++)
	{
		while(j&&s2[j+1]!=s2[i])
			j=nxt[j];
		if(s2[j+1]==s2[i])
			++j;
		nxt[i]=j;
	}
	int Ans=0;
	for(int i=1,j=0;i<=len1;i++)
	{
		while(j&&s2[j+1]!=s1[i])
			j=nxt[j];
		if(s2[j+1]==s1[i])
			++j;
		if(j==len2)
			++Ans,j=nxt[j];
	}
	return Ans;
}

struct BIT{
	int t[MAXS],siz;

	void C(int x,int v)
		{
			for(;x<=siz;x+=x&(-x))
				t[x]+=v;
		}

	int Q(int x)
		{
			if(!x)
				return 0;
			int Ret=0;
			for(;x;x-=x&(-x))
				Ret+=t[x];
			return Ret;
		}

	int Q(int l,int r){return Q(r)-Q(l-1);}
};

struct AC_Automaton{
	int cnt,rt;
	int son[MAXS][26],fail[MAXS],dfn[MAXN],dfn_end[MAXN],dft;
	vector<int> T[MAXS];
	BIT t;
	
	AC_Automaton(){cnt=rt=dft=0;}
	
	int insert()
		{
			int x=rt;
			for(int i=1;s[i];i++)
			{
				if(!son[x][s[i]-'a'])
					son[x][s[i]-'a']=++cnt;
				x=son[x][s[i]-'a'];
			}
			return x;
		}

	void dfs(int x)
		{
			dfn[x]=++dft;
			for(int _=0;_<T[x].size();_++)
				dfs(T[x][_]);
			dfn_end[x]=dft;
		}

	void build()
		{
			queue<int> q;
			for(int i=0;i<26;i++)
				if(son[rt][i])
					q.push(son[rt][i]);
			while(!q.empty())
			{
				int x=q.front();q.pop();
				for(int i=0;i<26;i++)
					if(son[x][i])
						fail[son[x][i]]=son[fail[x]][i],q.push(son[x][i]);
					else
						son[x][i]=son[fail[x]][i];
			}
			for(int i=1;i<=cnt;i++)
				T[fail[i]].push_back(i);
			dfs(rt);t.siz=dft;
		}

	void Change(int x,int dlt){t.C(dfn[x],dlt);}

	int Query(int x){return t.Q(dfn[x],dfn_end[x]);}
}M,Mr;

void predfs(int x,int fa)
{
	jmp[x][0]=fa;dep[x]=dep[fa]+1;
	for(int _=head[x];_;_=Edge[_].nxt)
	{
		int v=Edge[_].v;
		if(v==fa)
			continue;
		fac[v]=Edge[_].c;
		predfs(v,x);
	}
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int j=17;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			x=jmp[x][j];
	if(x==y) return x;
	for(int j=17;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

int JMP(int x,int stp)
{
	for(int j=17;~j;j--)
		if((stp>>j)&1)
			x=jmp[x][j];
	return x;
}

void dfs(int x,int fa,int p,int pr)
{
	M.Change(p,1);Mr.Change(pr,1);
	for(int _=0;_<Q1[x].size();_++)
		Ans[Q1[x][_].id]+=M.Query(Q1[x][_].p)*Q1[x][_].f;
	for(int _=0;_<Q2[x].size();_++)
		Ans[Q2[x][_].id]+=Mr.Query(Q2[x][_].p)*Q2[x][_].f;
	for(int _=head[x];_;_=Edge[_].nxt)
	{
		int v=Edge[_].v;
		if(v==fa) continue;
		dfs(v,x,M.son[p][Edge[_].c],Mr.son[pr][Edge[_].c]);
	}
	M.Change(p,-1);Mr.Change(pr,-1);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d%s",&u,&v,s+1);
		add(u,v,s[1]-'a');
		add(v,u,s[1]-'a');
	}
	predfs(1,0);
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d%s",&u,&v,s+1);
		int L=LCA(u,v),len=strlen(s+1),p=M.insert();
		reverse(s+1,s+1+len);
		int pr=Mr.insert();
		reverse(s+1,s+1+len);
		if(dep[u]+dep[v]-2*dep[L]<len) continue;
		if(u==L)
		{
			if(dep[v]-dep[u]>=len)
			{
				Q1[v].push_back((Qu){p,i,1});
				u=JMP(v,dep[v]-dep[u]-len+1);
				Q1[u].push_back((Qu){p,i,-1});
			}
		}
		else if(v==L)
		{
			if(dep[u]-dep[v]>=len)
			{
				Q2[u].push_back((Qu){pr,i,1});
				v=JMP(u,dep[u]-dep[v]-len+1);
				Q2[v].push_back((Qu){pr,i,-1});
			}
		}
		else
		{
			if(dep[v]-dep[L]>=len)
			{
				Q1[v].push_back((Qu){p,i,1});
				int tmp=JMP(v,dep[v]-dep[L]-len+1);
				Q1[tmp].push_back((Qu){p,i,-1});
			}
			if(dep[u]-dep[L]>=len)
			{
				Q2[u].push_back((Qu){pr,i,1});
				int tmp=JMP(u,dep[u]-dep[L]-len+1);
				Q2[tmp].push_back((Qu){pr,i,-1});
			}
			int len1=0,len2=len;
			int st=u,ed=v,top=0;
			if(dep[st]-dep[L]>len-1)
				st=JMP(st,dep[st]-dep[L]-len+1);
			if(dep[ed]-dep[L]>len-1)
				ed=JMP(ed,dep[ed]-dep[L]-len+1);
			while(st!=L)
				s1[++len1]=fac[st],st=jmp[st][0];
			while(ed!=L)
					stk[++top]=fac[ed],ed=jmp[ed][0];
			while(top)
				s1[++len1]=stk[top--];
			for(int j=1;j<=len2;j++)
				s2[j]=s[j]-'a';
			Ans[i]=Match(len1,len2);
		}
	}
	M.build();Mr.build();
	dfs(1,0,0,0);
	for(int i=1;i<=m;i++)
		printf("%d\n",Ans[i]);
}
