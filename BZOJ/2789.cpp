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

const int MAXN=1E6+10;

int n,t[MAXN];
char s[MAXN];
queue<int> q[26];
ll Ans;

void C(int x,int val)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=val;
}

int Q(int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		q[s[i]-'A'].push(i);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	{
		int v=q[s[i]-'A'].front();q[s[i]-'A'].pop();
		Ans+=Q(n)-Q(v-1);C(v,1);
	}
	printf("%lld\n",Ans);
}