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

const int MAXN=1E4+10;
const int MAXK=510;
const int MAXV=5510;

int n,k,Mx,a[MAXN],t[MAXK][MAXV];

void C(int x,int y,int v)
{
	for(++x;x<=k+1;x+=x&(-x))
		for(int Y=y;Y<=Mx;Y+=Y&(-Y))
			t[x][Y]=max(t[x][Y],v);
}

int Q(int x,int y)
{
	int ret=0;
	for(++x;x;x-=x&(-x))
		for(int Y=y;Y;Y-=Y&(-Y))
			ret=max(ret,t[x][Y]);
	return ret;
}

int main()
{
	int Ans=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),Mx=max(Mx,a[i]);
	Mx+=k;
	for(int i=1;i<=n;i++)
		for(int j=k;~j;j--)
		{
			int v=Q(j,a[i]+j)+1;
			Ans=max(Ans,v);
			C(j,a[i]+j,v);
		}
	printf("%d\n",Ans);
}