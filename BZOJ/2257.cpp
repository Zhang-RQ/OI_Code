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

	const int MAXN=1E3+10;

	set<int> s;
	int n,a[MAXN],k;

	void check(int x)
	{
		for(int i=1;i*i<=x;i++)
			if(x%i==0)
				s.insert(i),s.insert(x/i);
	}

	int main()
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),check(a[i]);
		for(set<int>::reverse_iterator it=s.rbegin();it!=s.rend();it++)
		{
			int tot=0;
			for(int i=1;i<=n;i++)
				if(a[i]%*it==0)
					++tot;
			if(tot>=k) return printf("%d\n",*it),0;
		}
	}