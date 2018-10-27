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

int n,m,mx,pos[MAXN],cnt;
bool vis[MAXN],chk[MAXN];
ll sum,Ans[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),chk[x]=1,mx=max(mx,x);
	for(int i=1;i<=mx;i++)
		pos[i]=i;
	scanf("%d",&m);
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		for(int j=pos[x],cur=0;cur<x&&j<=mx;j+=x)
		{
			pos[x]=j;
			if(vis[j]) continue;
			++cur;vis[j]=1;
			if(chk[j]) Ans[++cnt]=sum+cur;
		}
		sum+=x;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%lld\n",Ans[i]);
}