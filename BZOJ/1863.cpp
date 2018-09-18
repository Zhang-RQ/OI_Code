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

const int MAXN=20010;

int Ans=0,n,a[MAXN];
int mn[MAXN],mx[MAXN];

bool check(int x)
{
	mn[1]=mx[1]=a[1];
	for(int i=2;i<=n;i++)
	{
		mn[i]=max(a[i]-x+a[i-1]+a[1]-mx[i-1],0);
		mx[i]=min(a[1]-mn[i-1],a[i]);
	}
	return mn[n]==0;
}

int main()
{
	scanf("%d",&n);
	int L=0,R=1E9,Ans;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),L=max(L,a[i-1]+a[i]);
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(check(mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d\n",Ans);
}