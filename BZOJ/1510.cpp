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

const int MAXN=3E5+10;

int n,m,mn[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	mn[0]=1<<30;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		mn[i]=min(mn[i-1],x);
	}
	int p=n;
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		while(mn[p]<x) --p;
		if(p==0) return puts("0"),0;
		--p;
	}
	printf("%d\n",p+1);
}