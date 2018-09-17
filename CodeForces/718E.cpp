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

const int MAXN=1E5+10;
const int INF=0x3f3f3f3f;

bool vis[8];
int n,a[MAXN],dis[MAXN][8],d[MAXN],msk[MAXN],Dis[8][8],cnt[8][1<<8];
ll Ans[20];
char str[MAXN];
vector<int> v[8];
queue<int> q;

void BFS(int c)
{
	memset(d,0x3f,sizeof d);
	for(int x:v[c]) q.push(x),d[x]=0;
	memset(vis,0,sizeof vis);vis[c]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		if(!vis[a[x]])
		{
			for(int j:v[a[x]])
			{
				if(d[j]==INF) d[j]=d[x]+1,q.push(j);
			}
			vis[a[x]]=1;
		}
		if(x>1&&d[x-1]>d[x]+1) d[x-1]=d[x]+1,q.push(x-1);
		if(x<n&&d[x+1]>d[x]+1) d[x+1]=d[x]+1,q.push(x+1);
	}
	for(int i=1;i<=n;i++)
		dis[i][c]=d[i];
}

int main()
{
	scanf("%d",&n);
	scanf("%s",str+1);memset(Dis,0x3f,sizeof Dis);
	for(int i=1;i<=n;i++) a[i]=str[i]-'a',v[a[i]].push_back(i);
	for(int i=0;i<8;i++) BFS(i);
	for(int i=1;i<=n;i++)
		for(int j=0;j<8;j++)
			Dis[a[i]][j]=Dis[j][a[i]]=min(min(Dis[a[i]][j],dis[i][j]),Dis[j][a[i]]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<8;j++)
			msk[i]|=(dis[i][j]-Dis[a[i]][j])<<j;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=min(i+15,n);j++)
		{
			int tdis=j-i;
			for(int k=0;k<8;k++)
				tdis=min(tdis,dis[i][k]+dis[j][k]+1);
			Ans[tdis]++;
		}
	}
	for(int i=17;i<=n;i++)
	{
		cnt[a[i-16]][msk[i-16]]++;
		for(int s=0;s<1<<8;s++)
		{
			for(int j=0;j<8;j++)
			{
				if(!cnt[j][s]) continue;
				int tdis=INF;
				for(int k=0;k<8;k++)
					tdis=min(tdis,Dis[k][j]+((s>>k)&1)+dis[i][k]+1);
				Ans[tdis]+=cnt[j][s];
			}
		}
	}
	for(int i=15;~i;--i) if(Ans[i]) {printf("%d %lld\n",i,Ans[i]);break;}
}