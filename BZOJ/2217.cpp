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

int n,m,L[MAXN<<1],R[MAXN<<1],ext[MAXN],sum;
char s[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=n;i;i--)
		ext[i]=s[i]=='T'?ext[i+1]+1:0;
	for(int i=1;i<=n;i++)
	{
		sum+=s[i]=='T'?2:1;
		L[sum]=1;R[sum]=i;
		if(s[i]=='T')
		{
			if(ext[1]<ext[i]) L[sum-1]=ext[1]+2,R[sum-1]=i+ext[1];
			else if(i+ext[i]<=n) L[sum-1]=ext[i]+1,R[sum-1]=i+ext[i]; 
		}
	}
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		if(x>sum) puts("NIE");
		else if(L[x]) printf("%d %d\n",L[x],R[x]);
		else puts("NIE");
	}
}