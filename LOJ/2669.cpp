#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

int n,stk[MAXN],inR[MAXN],vis[MAXN],top,Faw[MAXN],a[MAXN];
vector<int> Ring;
ll Ans1,Ans2,S[MAXN],f[MAXN],pre1[MAXN],pre2[MAXN],suf1[MAXN],suf2[MAXN];
vector<pair<int,int> > T[MAXN];

void Find_Ring(int x,int fa)
{
	stk[++top]=x;vis[x]=1;
	for(auto e:T[x])
		if(e.first!=fa)
		{
			Faw[e.first]=e.second;
			if(vis[e.first])
				throw e.first;
			Find_Ring(e.first,x);
		}
	--top;
}

void dfs(int x,int fa)
{
	for(auto e:T[x])
		if(e.first!=fa&&!inR[e.first])
		{
			dfs(e.first,x);
			Ans1=max(Ans1,f[x]+f[e.first]+e.second);
			f[x]=max(f[x],f[e.first]+e.second);
		}
}

int main()
{
	memset(pre1,0xcf,sizeof pre1);
	memset(pre2,0xcf,sizeof pre2);
	memset(suf1,0xcf,sizeof suf1);
	memset(suf2,0xcf,sizeof suf2);
	scanf("%d",&n);
	for(int i=1,u,v,w;i<=n;i++)
		scanf("%d%d%d",&u,&v,&w),
		T[u].emplace_back(v,w),
		T[v].emplace_back(u,w);
	try{Find_Ring(1,0);}
	catch(int beg)
	{
		for(int i=1;i<=top;i++)
		{
			if(i==1)
			{
				while(stk[i]!=beg)
					++i;
			}
			Ring.push_back(stk[i]);
			inR[stk[i]]=1;
		}
	}
	for(int x:Ring)
		dfs(x,0);
	int rs=Ring.size();
	for(int i=0;i<rs;i++)
		a[i+1]=Ring[i];
	for(int i=1;i<=rs;i++)
		S[i]=S[i-1]+Faw[a[i]];
	ll tmp=-1E18;
	for(int i=1;i<=rs;i++)
	{
		pre1[i]=max(pre1[i-1],f[a[i]]+S[i]);
		pre2[i]=max(pre2[i-1],f[a[i]]+S[i]+tmp);
		tmp=max(tmp,f[a[i]]-S[i]);
	}
	tmp=-1E18;
	for(int i=rs;i;i--)
	{
		suf1[i]=max(suf1[i+1],f[a[i]]-S[i]);
		suf2[i]=max(suf2[i+1],f[a[i]]-S[i]+tmp);
		tmp=max(tmp,f[a[i]]+S[i]);
	}
	Ans2=suf2[1];
	for(int i=1;i<rs;i++)//i...i+1
		Ans2=min(Ans2,max(S[rs]+pre1[i]+suf1[i+1],max(pre2[i],suf2[i+1])));
	printf("%.1lf\n",1.0*max(Ans1,Ans2)/2);
}
