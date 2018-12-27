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

const int MAXN=1E7+10;
const unsigned int base=12345;

int n,m,a[MAXN],cnt[MAXN],len;
ull pw[MAXN],tar,now;

int main()
{
	scanf("%d%d",&n,&m);
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*base;
	for(int i=1;i<=m;i++)scanf("%d",&cnt[i]);
	for(int i=1,x;i<=m;i++) scanf("%d",&x),len+=cnt[i],tar+=pw[x]*cnt[i];
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int l=1,r=len;
	for(int i=l;i<=r;i++) now+=pw[a[i]];
	int Ans=0;
	while(r<=n)
	{
		if(now==tar) ++Ans;
		now+=pw[a[++r]];
		now-=pw[a[l++]];
	}
	printf("%d\n",Ans);
}