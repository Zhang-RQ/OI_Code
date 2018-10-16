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

const int MAXN=1E4+10;
const int MAXM=2E4+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,n,d[MAXN],mid,f[MAXN];
int ok;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

bool Check(vector<int> &v,int p)
{
	for(int i=0,j=v.size()-1;i<j;i++,j--)
	{
		if(i==p) ++i;
		if(j==p) --j;
		if(v[i]+v[j]>mid) return 0;
	}
	return 1;
}

void dfs(int x,int fa)
{
	vector<int> ve;f[x]=0;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);
		ve.push_back(f[v]+1);
	}
	if(!ve.size()) return;
	if(x==1&&(~ve.size()&1))
	{
		sort(ve.begin(),ve.end());
		for(int i=0,j=ve.size()-1;i<j;i++,j--)
			if(ve[i]+ve[j]>mid) ok=0;
		return;
	}
	if(~ve.size()&1) ve.push_back(0);
	sort(ve.begin(),ve.end());
	int L=0,R=ve.size()-1,Ans=-1;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(Check(ve,mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	if(Ans==-1) f[x]=23333;
	else f[x]=ve[Ans];
	ok&=f[x]<=mid;
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),add(u,v),add(v,u),d[u]++,d[v]++;
	int L=0,R=n,Ans=0;
	while(L<=R)
	{
		mid=(L+R)>>1;
		ok=1;dfs(1,0);
		if(ok) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	int Ans1=1;
	for(int i=1;i<=n;i++)
		Ans1+=(d[i]-1)>>1;
	printf("%d %d\n",Ans1,Ans);
}