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

int n,m,S1[1<<10],S2[1<<10],f[1<<10][1<<10];

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),S1[1<<(i-1)]=x;
	scanf("%d",&m);
	for(int i=1,x;i<=m;i++)
		scanf("%d",&x),S2[1<<(i-1)]=x;
	for(int i=0;i<n;i++)
		for(int s=0;s<1<<n;s++)
			if((s>>i)&1)
				S1[s]+=S1[s^(1<<i)];
	for(int i=0;i<m;i++)
		for(int s=0;s<1<<m;s++)
			if((s>>i)&1)
				S2[s]+=S2[s^(1<<i)];
	for(int s1=1;s1<1<<n;s1++)
		for(int s2=1;s2<1<<m;s2++)
		{
			for(int i=0;i<n;i++)
				if((s1>>i)&1)
					f[s1][s2]=max(f[s1][s2],f[s1^(1<<i)][s2]);
			for(int i=0;i<m;i++)
				if((s2>>i)&1)
					f[s1][s2]=max(f[s1][s2],f[s1][s2^(1<<i)]);
			if(S1[s1]==S2[s2])
				f[s1][s2]++;
		}
	printf("%d\n",n+m-2*f[(1<<n)-1][(1<<m)-1]);
}