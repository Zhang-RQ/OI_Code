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

const int MAXN=260;

int n,W;
int w[MAXN],t[MAXN];
double f[1010],v[MAXN];

bool check(double mid)
{
	for(int i=1;i<=n;i++) v[i]=t[i]-mid*w[i];
	for(int j=0;j<=W;j++)
		f[j]=-10000000000;
	f[0]=0;
	for(int i=1;i<=n;i++)
		for(int j=W;j>=0;j--)
		{
			if(f[j]<-100000000) continue;
			int nxt=min(W,j+w[i]);
			f[nxt]=max(f[nxt],f[j]+v[i]);
		}
	return f[W]>=0;
}

int main()
{
	scanf("%d%d",&n,&W);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&w[i],&t[i]);
	double L=0,R=1E6;
	for(int i=1;i<=70;i++)
	{
		double mid=(L+R)/2;
		if(check(mid)) L=mid;
		else R=mid;
	}
	printf("%lld\n",(ll)(1000*R));
}