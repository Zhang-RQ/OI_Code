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

const int MAXN=501000;

bool vis[MAXN];
int n,m;
ll s[MAXN],Ans,x;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&x),s[i]=s[i-1]^x;
	for(int j=62;~j;j--)
	{
		int cnt=0;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&!((s[i]>>j)&1))
				++cnt;
		if(cnt>=m&&!((s[n]>>j)&1))
		{
			for(int i=1;i<=n;i++)
				if((s[i]>>j)&1)
					vis[i]=1;
		}
		else Ans|=1ll<<j;
	}
	printf("%lld\n",Ans);
}