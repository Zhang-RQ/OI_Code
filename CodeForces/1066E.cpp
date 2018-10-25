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

const int P=998244353;
const int MAXN=2E5+10;

ll pw[MAXN],Ans;
int n,m,sum[MAXN];
char s1[MAXN],s2[MAXN];

int main()
{
	scanf("%d%d",&n,&m);pw[0]=1;
	scanf("%s%s",s1+1,s2+1);
	reverse(s1+1,s1+1+n);reverse(s2+1,s2+1+m);
	for(int i=1;i<=max(n,m);i++)
		pw[i]=(pw[i-1]<<1)%P;
	for(int i=m;i>=1;i--)
		sum[i]=sum[i+1]+(s2[i]=='1');
	for(int i=1;i<=n;i++)
		if(s1[i]=='1')
			(Ans+=sum[i]*pw[i-1]%P)%=P;
	printf("%lld\n",Ans);
}