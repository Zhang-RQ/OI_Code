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

int k,tot;
pair<int,int> s[MAXN],t[4];

int main()
{
	scanf("%d",&k);
	for(int i=1,n;i<=k;i++)
	{
		scanf("%d",&n);
		for(int j=1,l;j<=n;j++)
			scanf("%d",&l),s[++tot]=make_pair(l,i);
	}
	sort(s+1,s+1+tot);
	for(int i=1;i<=tot;i++)
	{
		int f=0;
		for(int j=1;j<=3;j++)
			if(t[j].second==s[i].second)
				{f=1;t[j]=s[i];break;}
		if(!f) t[1]=s[i];
		sort(t+1,t+4);
		if(t[1].first+t[2].first>t[3].first)
			printf("%d %d %d %d %d %d\n",t[1].second,t[1].first,t[2].second,t[2].first,t[3].second,t[3].first),exit(0);
	}
	puts("NIE");
}