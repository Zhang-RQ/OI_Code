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

int n,m,Ans;
ll sum,sum2;
set<ll> s;

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),sum+=x,s.insert(sum);
	scanf("%d",&m);
	for(int i=1,x;i<=m;i++) scanf("%d",&x),sum2+=x,Ans+=s.find(sum2)!=s.end();
	if(sum!=sum2) Ans=0;
	printf("%d\n",Ans?Ans:-1);
}