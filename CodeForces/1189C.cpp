#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

int n,q,a[MAXN],lg2[MAXN];
int res[20][MAXN],ans[20][MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),res[0][i]=a[i];
	for(int i=2;i<=n;i++)
		lg2[i]=lg2[i>>1]+1;
	for(int j=1;j<=lg2[n];j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			res[j][i]=(res[j-1][i]+res[j-1][i+(1<<(j-1))])%10,
			ans[j][i]=ans[j-1][i]+ans[j-1][i+(1<<(j-1))]+(res[j-1][i]+res[j-1][i+(1<<(j-1))]>=10);
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		printf("%d\n",ans[lg2[r-l+1]][l]);
	}
}
