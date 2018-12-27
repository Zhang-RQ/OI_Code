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

const int MAXN=1010;

int n,Ans1,Ans2;
map<int,int> mp;
vector<int> v[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),Ans2=max(++mp[x],Ans2);
	Ans1=mp.size();
	if(Ans1<Ans2)
	{
		printf("%d %d\n",Ans1,1);
		for(auto i:mp)
		{
			printf("%d ",i.second);
			for(int j=1;j<=i.second;j++)
				printf("%d%c",i.first,j==i.second?'\n':' ');
		}
	}
	else
	{
		printf("%d %d\n",Ans2,2);
		for(auto i:mp)
			for(int j=1;j<=i.second;j++)
				v[j].push_back(i.first);
		for(int i=1;i<=Ans2;i++)
		{
			printf("%d ",v[i].size());
			for(int j=0;j<v[i].size();j++)
				printf("%d%c",v[i][j],j==v[i].size()-1?'\n':' ');
		}
	}
}