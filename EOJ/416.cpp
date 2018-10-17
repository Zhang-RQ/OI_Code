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

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	if(m==0) return printf("%d\n",n),0;
	if(m<n)
	{
		printf("%d\n",n-1);
		for(int i=1;i<=m;i++)
			printf("%d %d\n",i,i+1);
	}
	else
	{
		int ans=n-1;
		vector<pair<int,int> > v;
		for(int i=1;i<n;i++)
			v.push_back({i,i+1}),m--;
		for(int i=3;i<=n;i++)
		{
			if(!m) break;
			ans--;
			for(int j=1;j<i-1;j++)
			{
				if(!m) break;
				v.push_back({j,i});
				--m;
			}
		}
		printf("%d\n",ans);
		for(auto o:v)
			printf("%d %d\n",o.first,o.second);
	}
}