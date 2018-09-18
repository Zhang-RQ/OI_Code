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

const int MAXN=2.5E5+10;

int n,Ans;
int stk[MAXN],top;

int main()
{
	scanf("%d",&n);Ans=n;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%*d%d",&x);
		while(top&&stk[top]>x) --top;
		if(stk[top]==x) --Ans;
		else stk[++top]=x;
	}
	printf("%d\n",Ans);
}