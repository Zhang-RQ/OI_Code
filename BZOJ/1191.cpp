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

int mp[1001][1001],lk[1001];
int n,m;
bool y[1001];

bool find(int x)
{
	for(int i=0;i<n;i++)
	{
	   if(!y[i]&&mp[x][i])
	   {
	   	   y[i]=1;
	   	   if(!lk[i]||find(lk[i]))
	   	   {
	   	   	  lk[i]=x;
	   	   	  return 1;
	   	   }
	   }
    }
    return 0;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
	   int x,y;
	   scanf("%d%d",&x,&y);
	   mp[i][x]=mp[i][y]=1;
    }
    int ans=0;
    for(int i=1;i<=m;i++)
    {
    	memset(y,0,sizeof(y));
    	if(find(i))ans++;
    	else break;
    }
   	printf("%d\n",ans);
	return 0;
}