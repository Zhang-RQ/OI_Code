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

const int MAXN=2E5+10;

int n,m,k;
int a[MAXN];

bool check(int Mid)
{
	int lst=0,cnt=0;
	for(int i=Mid;i<=n;i++)
	{
		if(a[i]>k||cnt>m) return false;
		if(a[i]>lst) ++cnt,lst=k-a[i];
		else lst-=a[i];
	}
	return cnt<=m;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int L=1,R=n+1,Ans=0;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(check(mid)) R=mid-1,Ans=mid;
		else L=mid+1;
	}
	printf("%d\n",n-Ans+1);
}