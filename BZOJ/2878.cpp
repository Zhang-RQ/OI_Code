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

const int MAXN=1E5+10;

double dwn[MAXN],up[MAXN],f[MAXN],Ans;
int stk[MAXN],stkv[MAXN],top,son[MAXN],n,m,preV[MAXN];
bool inR[MAXN],ins[MAXN];
vector<pair<int,int> >g[MAXN];
vector<int> R;

int pre(int x){return (x-1+R.size())%R.size();}
int nxt(int x){return (x+1)%R.size();}

void find_R(int x,int fa)
{
	if(R.size()) return;
	ins[x]=1;stk[++top]=x;
	for(pair<int,int> v:g[x])
		if(v.first!=fa)
		{
			if(R.size()) return;
			if(!ins[v.first]) stkv[top]=v.second,find_R(v.first,x);
			else
			{
				stkv[top]=v.second;
				while(stk[top]!=v.first) R.push_back(stk[top]),preV[stk[top]]=stkv[top],inR[stk[top]]=1,top--;
				R.push_back(stk[top]);inR[stk[top]]=1;preV[stk[top]]=stkv[top];top--;top=0;
				return;
			}
		}
	ins[x]=0;--top;
}

void dfs1(int x,int fa)
{
	for(pair<int,int> v:g[x])
		if(v.first!=fa&&!inR[v.first])
			++son[x];
	for(pair<int,int> v:g[x])
		if(v.first!=fa&&!inR[v.first])
			dfs1(v.first,x),dwn[x]+=dwn[v.first]+v.second;
	if(son[x]) dwn[x]/=son[x];
}

void dfs2(int x,int fa,int fav)
{
	if(!R.size())
	{
		if(son[fa]>1) up[x]=(up[fa]+dwn[fa]*son[fa]-(dwn[x]+fav))/(son[fa]-(fa==1))+fav;
		else up[x]=up[fa]+fav;
	}
	else if(!inR[x])
	{
		if(inR[fa]) up[x]=(up[fa]*2+dwn[fa]*son[fa]-(dwn[x]+fav))/(son[fa]+1)+fav;
		else if(son[fa]>1) up[x]=(up[fa]+dwn[fa]*son[fa]-(dwn[x]+fav))/son[fa]+fav;
		else up[x]=up[fa]+fav;
	}
	for(pair<int,int> v:g[x])
		if(v.first!=fa&&!inR[v.first])
			dfs2(v.first,x,v.second);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),g[u].push_back(make_pair(v,w)),g[v].push_back(make_pair(u,w));
	find_R(1,0);
	if(!R.size())  
	{
		dfs1(1,0),dfs2(1,0,0);
		Ans+=dwn[1];
		for(int i=2;i<=n;i++)
			Ans+=(up[i]+dwn[i]*son[i])/(son[i]+1);
	}
	else
	{
		for(int i=0;i<R.size();i++) dfs1(R[i],0);
		for(int i=0,pos,lpos;i<R.size();i++)
		{
			pos=pre(i);
			f[R[pos]]=dwn[R[pos]];
			while(pre(pos)!=i)
			{
				lpos=pos;pos=pre(pos);
				if(son[R[pos]]) f[R[pos]]=((f[R[lpos]]+preV[R[lpos]])+dwn[R[pos]]*son[R[pos]])/(son[R[pos]]+1);
				else f[R[pos]]=f[R[lpos]]+preV[R[lpos]];
			}
			f[R[i]]=(f[R[pos]]+preV[R[i]])/2;
			pos=nxt(i);
			f[R[pos]]=dwn[R[pos]];
			while(nxt(pos)!=i)
			{
				lpos=pos;pos=nxt(pos);
				if(son[R[pos]]) f[R[pos]]=((f[R[lpos]]+preV[R[nxt(lpos)]])+dwn[R[pos]]*son[R[pos]])/(son[R[pos]]+1);
				else f[R[pos]]=f[R[lpos]]+preV[R[nxt(lpos)]];
			}
			f[R[i]]+=(f[R[pos]]+preV[R[nxt(i)]])/2;
			up[R[i]]=f[R[i]];
			dfs2(R[i],0,0);
		}
		for(int i=1;i<=n;i++) 
			if(!inR[i]) Ans+=(dwn[i]*son[i]+up[i])/(son[i]+1);
			else Ans+=(2*up[i]+dwn[i]*son[i])/(son[i]+2);
	}
	printf("%.5lf\n",Ans/n);
}