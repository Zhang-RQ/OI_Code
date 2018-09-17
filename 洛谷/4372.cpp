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

const int MAXN=1E5+10;

int a[MAXN],t[MAXN],n;
pair<int,int> v[MAXN];
ll Ans;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&v[i].first),v[i].second=i;
	if(n==1) return puts("0"),0;
	sort(v+1,v+1+n);
	for(int i=1,mx=0;i<n;i++) t[i]=(mx=max(mx,v[i].second))-i;
	for(int i=1;i<=n;i++) Ans+=max(max(t[i-1],t[i]),1);
	printf("%lld\n",Ans);
}