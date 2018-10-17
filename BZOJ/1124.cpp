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

const int MAXN=1E6+10;

int n,a[MAXN],d[MAXN];
int Ans1,Ans2;

namespace solve_mn{
	queue<int> q;
	int de[MAXN];
	bool vis[MAXN],dead[MAXN];
	void solve()
	{
		memcpy(de,d,sizeof d);
		for(int i=1;i<=n;i++)
			if(!de[i])
				q.push(i);
		while(!q.empty())
		{
			int x=q.front();
			q.pop();
			vis[x]=1;
			if(!dead[a[x]])
			{
				Ans1++;
				if(!--de[a[a[x]]])
					q.push(a[a[x]]);
				vis[a[x]]=dead[a[x]]=1;
			}
		}
		for(int i=1;i<=n;i++)
			if(!vis[i])
			{
				int x=i,cnt=0;
				while(1)
				{
					if(vis[x]) break;
					vis[x]=1;x=a[x];
					++cnt;
				}
				Ans1+=(cnt+1)>>1;
			}
	}
}

namespace solve_mx{
	
	struct __edge{
		int v,nxt;
	}Edge[MAXN<<1];
	
	int head[MAXN],cnt_e,de[MAXN];
	int stk[MAXN],top;
	bool vis[MAXN];

	void add(int u,int v)
	{
		Edge[++cnt_e].v=v;
		Edge[cnt_e].nxt=head[u];
		head[u]=cnt_e;
	}

	void BFS(int i)
	{
		queue<int> q;
		q.push(i);vis[i]=1;
		while(!q.empty())
		{
			int x=q.front();q.pop();
			stk[++top]=x;
			for(int i=head[x];i;i=Edge[i].nxt)
			{
				int v=Edge[i].v;
				if(vis[v]) continue;
				q.push(v);vis[v]=1;
			}
		}
	}

	void solve()
	{
		memcpy(de,d,sizeof d);
		for(int i=1;i<=n;i++)
			add(i,a[i]),add(a[i],i);
		for(int i=1;i<=n;i++)
		{
			if(vis[i]) continue;
			int cnt=0;top=0;
			BFS(i);
			if(top==1) Ans2++;
			else
			{
				for(int j=1;j<=top;j++)
					cnt+=(de[stk[j]]==0);
				if(!cnt) Ans2+=top-1;
				else Ans2+=top-cnt;
			}
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),d[a[i]]++;
	solve_mn::solve();solve_mx::solve();
	printf("%d %d\n",Ans1,Ans2);
}