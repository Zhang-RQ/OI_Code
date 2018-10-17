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

const int MAXN=2010;
const int P=10;

ll Ans[MAXN][MAXN],stk[15][MAXN];
int n,m,a[MAXN];

void solve(int L,int R,int dep)
{
	if(L==R)
	{
		for(int i=1;i<=m;i++)
			Ans[L][i]=stk[dep][i]%P;
		return;
	}
	int mid=(L+R)>>1;
	memcpy(stk[dep+1],stk[dep],sizeof stk[dep+1]);
	for(int i=mid+1;i<=R;i++)
		for(int j=m;j>=a[i];j--)
			(stk[dep+1][j]+=stk[dep+1][j-a[i]])%=P;
	solve(L,mid,dep+1);
	memcpy(stk[dep+1],stk[dep],sizeof stk[dep+1]);
	for(int i=L;i<=mid;i++)
		for(int j=m;j>=a[i];j--)
			(stk[dep+1][j]+=stk[dep+1][j-a[i]])%=P;
	solve(mid+1,R,dep+1);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	stk[1][0]=1;
	solve(1,n,1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%lld",Ans[i][j]);
		puts("");
	}
}