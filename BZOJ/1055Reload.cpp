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

const int MAXN=210;

map<char,int> mp;

char str[MAXN];
int W,I,N,G,n;
bool f[4][MAXN][MAXN],ok[4][4][4],fafa;

int main()
{
	mp['W']=0;mp['I']=1;mp['N']=2;mp['G']=3;
	scanf("%d%d%d%d",&W,&I,&N,&G);
	for(int i=1;i<=W;i++)
	{
		scanf("%s",str+1);
		ok[mp['W']][mp[str[1]]][mp[str[2]]]=1;
	}
	for(int i=1;i<=I;i++)
	{
		scanf("%s",str+1);
		ok[mp['I']][mp[str[1]]][mp[str[2]]]=1;
	}
	for(int i=1;i<=N;i++)
	{
		scanf("%s",str+1);
		ok[mp['N']][mp[str[1]]][mp[str[2]]]=1;
	}
	for(int i=1;i<=G;i++)
	{
		scanf("%s",str+1);
		ok[mp['G']][mp[str[1]]][mp[str[2]]]=1;
	}
	scanf("%s",str+1);n=strlen(str+1);
	for(int i=1;i<=n;i++)
		f[mp[str[i]]][i][i]=1;
	for(int len=2;len<=n;len++)
		for(int j=0;j<4;j++)
			for(int c1=0;c1<4;c1++)
				for(int c2=0;c2<4;c2++)
					if(ok[j][c1][c2])
						for(int L=1;L+len-1<=n;L++)
							for(int len1=1;len1<len;len1++)
								f[j][L][L+len-1]|=f[c1][L][L+len1-1]&&f[c2][L+len1][L+len-1];
	if(f[0][1][n]) fafa=1,putchar('W');
	if(f[1][1][n]) fafa=1,putchar('I');
	if(f[2][1][n]) fafa=1,putchar('N');
	if(f[3][1][n]) fafa=1,putchar('G');
	if(!fafa) puts("The name is wrong!");
}