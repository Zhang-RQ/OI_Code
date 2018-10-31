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

const int P=1E9+7;
const int MAXN=2E5+10;
const int MAXM=2E5+10;

struct __edge{
	int v,nxt,id;
}Edge[MAXM];

int head[MAXN],cnt_e,stk[MAXN],top,siz,Esiz,Vsiz,n,d[MAXN];
bool ins[MAXN],vis[MAXN],fafa;
ll Ans=1;

void add(int u,int v,int id)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].id=id;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int eid)
{
	if(!siz) stk[++top]=x,ins[x]=1;
	vis[x]=1;
	++Vsiz;Esiz+=d[x];
	for(int i=head[x];i;i=Edge[i].nxt)
		if(Edge[i].id!=eid)
		{
			int v=Edge[i].v;
			if(!ins[v])
				dfs(v,Edge[i].id);
			else if(!siz)
			{
				int _top=top;
				while(stk[top]!=v)
					++siz,--top;
				++siz;top=_top;
			}
		}
	if(!siz) --top,ins[x]=0;
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<=n;i++)
		scanf("%d%d",&u,&v),add(u,v,i),add(v,u,i),d[u]++,d[v]++;
	for(int i=1;i<=2*n;i++)
		if(!vis[i])
		{
			top=siz=Esiz=Vsiz=0;
			dfs(i,0);Esiz/=2;
			if(Esiz==Vsiz-1) Ans=Ans*Vsiz%P;
			else if(Esiz==Vsiz&&siz>1) Ans=Ans*2%P;
		}
	printf("%d\n",Ans);
}