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

const int MAXN=1650;

int n,m,siz,X[MAXN];
bitset<MAXN> a[MAXN];

int id(int x,int y){return (x-1)*m+y;}

void solve()
{
	for(int i=1,pos;i<=siz;i++)
	{
		pos=0;
		for(int j=i;j<=siz;j++)
			if(a[j][i]) pos=j;
		if(!pos) continue;
		if(pos!=i) swap(a[pos],a[i]);
		for(int j=i+1;j<=siz;j++)
			if(a[j][i])
				a[j]^=a[i];
	}
	for(int i=siz;i>=1;i--)
	{
		if(!a[i][i]) X[i]=1;
		else X[i]=a[i][0];
		if(X[i])
			for(int j=i-1;j>=1;j--)
				if(a[j][i])
					a[j][0]=a[j][0]^1;
	}
}

int main()
{
	scanf("%d%d",&n,&m);siz=n*m;
	for(int i=1,Id;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			Id=id(i,j);
			if(i>1) a[Id][id(i-1,j)]=1;
			if(i<n) a[Id][id(i+1,j)]=1;
			if(j>1) a[Id][id(i,j-1)]=1;
			if(j<m) a[Id][id(i,j+1)]=1;
			a[Id][Id]=1;
		}
	solve();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			printf("%d%c",X[id(i,j)],j==m?'\n':' ');
}