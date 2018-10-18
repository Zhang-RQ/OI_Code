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

const int MAXN=30010;
const int MAXL=205;
const int base=131;

int n,l;
char s[MAXL];
ll Ans;
ull hsh[MAXN][MAXL],pw[MAXL];
map<ull,int> mp;

namespace Hash_table{
	const int P=786433;
	const int MAXND=MAXN*3;
	int head[P],nxt[MAXND],v[MAXND],cnt;
	ull key[MAXND];
	void clear()
	{
		memset(head,0,sizeof head);
		cnt=0;
	}
	void insert(ull Key)
	{
		int idx=Key%P,f=0;
		for(int i=head[idx];i;i=nxt[i])
			if(key[i]==Key)
				v[i]++,f=1;
		if(!f)
		{
			++cnt;
			key[cnt]=Key;
			v[cnt]=1;
			nxt[cnt]=head[idx];
			head[idx]=cnt;
		}
	}
	int Query(ull Key)
	{
		int idx=Key%P;
		for(int i=head[idx];i;i=nxt[i])
			if(key[i]==Key)
				return v[i];
		return 0;
	}
}

int main()
{
	scanf("%d%d%*d",&n,&l);
	pw[0]=1;
	for(int i=1;i<=l;i++)
		pw[i]=pw[i-1]*base;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;s[j];j++)
			hsh[i][j]=hsh[i][j-1]*base+s[j];
	}
	for(int i=1;i<=l;i++)
	{
		Hash_table::clear();
		for(int j=1;j<=n;j++)
		{
			ull T=hsh[j][i-1]*pw[l-i]+hsh[j][l]-hsh[j][i]*pw[l-i];
			Ans+=Hash_table::Query(T);Hash_table::insert(T);
		}
	}
	printf("%lld\n",Ans);
}