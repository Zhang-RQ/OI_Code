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
#include<bitset>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E6+10;

int n;
bitset<MAXN> s;

int main()
{
	int Ans=0;s[0]=1;
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),s=s^(s<<x);
	for(int i=1;i<MAXN;i++)
		if(s[i])
			Ans^=i;
	printf("%d\n",Ans);
}