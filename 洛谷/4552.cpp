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

int n,a[MAXN];
ll b[MAXN],A,B;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		b[i]=a[i]-a[i-1];
	for(int i=2;i<=n;i++)
		if(b[i]>0) A+=b[i];
		else B-=b[i];
	printf("%lld\n%lld\n",max(A,B),max(A,B)-min(A,B)+1);
}