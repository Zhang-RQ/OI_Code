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
const ll INF=1ll<<60;

int n,c,p[MAXN],s[MAXN];
ll f[2][MAXN],Ans;

int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	for(int i=1,now;i<=n;i++)
	{
		now=i&1;Ans+=min(s[i],p[i]);
		for(int j=0;j<=i;j++)
		{
			f[now][j]=INF;
			if(p[i]>s[i])
			{
				if(i!=j) f[now][j]=min(f[now][j],f[now^1][j]+p[i]-s[i]+1ll*c*j);
				if(j) f[now][j]=min(f[now][j],f[now^1][j-1]);
			}
			else
			{
				if(i!=j) f[now][j]=min(f[now][j],f[now^1][j]+1ll*c*j);
				if(j) f[now][j]=min(f[now][j],f[now^1][j-1]+s[i]-p[i]);
			}
		}
	}
	ll Ans2=INF;
	for(int i=0;i<=n;i++) Ans2=min(Ans2,f[n&1][i]);
	cout<<Ans+Ans2<<endl;
}