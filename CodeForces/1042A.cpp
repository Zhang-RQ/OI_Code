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

const int MAXN=110;

int n,m,Ans1,Ans2,a[MAXN];

bool check(int mid)
{
	int Cnt=0;
	for(int i=1;i<=n;i++)
		Cnt+=mid-a[i];
	return Cnt<=m;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),Ans2=max(Ans2,a[i]+m);
	int L=Ans2-m,R=1E7,Ans1=Ans2-m;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(check(mid)) Ans1=mid,L=mid+1;
		else R=mid-1;
	}
	for(int i=1;i<=n;i++)
		m-=Ans1-a[i];
	if(m>0) ++Ans1;
	printf("%d %d\n",Ans1,Ans2);
}