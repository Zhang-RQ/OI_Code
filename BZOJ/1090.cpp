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

const int MAXN=110;
const ull base=233333;

char s[MAXN];
int n,f[MAXN][MAXN];
ull hsh[MAXN],pw[MAXN];

inline ull get(int l,int r){return hsh[r]-hsh[l-1]*pw[r-l+1];}

void solve(int l,int r)
{
	ull H=get(l,r);
	for(int j=r+1,cnt=2;j+r-l<=n;j+=r-l+1,cnt++)
	{
		if(get(j,j+r-l)==H)
			f[l][j+r-l]=min(f[l][j+r-l],f[l][r]+2+(cnt>=10?2:1));
		else break;
	}
}

int main()
{
	scanf("%s",s+1);pw[0]=1;
	n=strlen(s+1);memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;i++)
		hsh[i]=hsh[i-1]*base+s[i]-'A',pw[i]=pw[i-1]*base;
	for(int i=1;i<=n;i++)
		f[i][i]=1,solve(i,i);
	for(int len=2;len<=n;len++)
	{
		for(int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			for(int j=l;j<r;j++)
				f[l][r]=min(f[l][r],f[l][j]+f[j+1][r]);
			solve(l,r);
		}
	}
	printf("%d\n",f[1][n]);
}