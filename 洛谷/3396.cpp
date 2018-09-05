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

const int MAXN=150010;
const int MAXS=401;

int n,m,v[MAXN],lim;
int Ans[MAXS][MAXS];
char str[10];

int main()
{
	scanf("%d%d",&n,&m);
	lim=sqrt(n);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=lim;j++)
			Ans[j][i%j]+=v[i];
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%s%d%d",str+1,&x,&y);
		if(str[1]=='A')
		{
			if(x<=lim) printf("%d\n",Ans[x][y]);
			else 
			{
				int Res=0;
				for(int j=y;j<=n;j+=x)
					Res+=v[j];
				printf("%d\n",Res);
			}
		}
		else
		{
			for(int j=1;j<=lim;j++)
				Ans[j][x%j]-=v[x];
			v[x]=y;
			for(int j=1;j<=lim;j++)
				Ans[j][x%j]+=v[x];
		}
	}
}