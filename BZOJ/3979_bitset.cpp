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

const int MAXN=80;

bitset<MAXN> g[MAXN];
char str[MAXN];
int n,Ans=0;

bool check1()
{
	for(int i=1;i<=n;i++)
		if(g[i].count()==n) return 1;
	return 0;
}

bool check2()
{
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			if((g[i]|g[j]).count()==n) return 1;
	return 0;
}

bool check3()
{
	for(int i=3;i<=n;i++)
		for(int j=2;j<i;j++)
			for(int k=1;k<j;k++)
				if((g[i]|g[j]|g[k]).count()==n) return 1;
	return 0;
}

bool check4()
{
	for(int i=4;i<=n;i++)
		for(int j=3;j<i;j++)
			for(int k=2;k<j;k++)
				for(int l=1;l<k;l++)
					if((g[i]|g[j]|g[k]|g[l]).count()==n) return 1;
	return 0;
}

bool check5()
{
	for(int i=5;i<=n;i++)
		for(int j=4;j<i;j++)
			for(int k=3;k<j;k++)
				for(int l=2;l<k;l++)
					for(int m=1;m<l;m++)
						if((g[i]|g[j]|g[k]|g[l]|g[m]).count()==n) return 1;
	return 0;
}

int main()
{
	int Cs=0;
	srand((ull)new char);
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)
		{
			g[i].reset();
			scanf("%s",str+1);
			for(int j=1;j<=n;j++)
				if(str[j]=='1') g[i].set(j);
			g[i].set(i);
		}
		if(check1()) Ans=1;
		else if(check2()) Ans=2;
		else if(check3()) Ans=3;
		else if(check4()) Ans=4;
		else if(check5()) Ans=5;
		else Ans=6;
		printf("Case %d: %d\n",++Cs,Ans);
	}
}
