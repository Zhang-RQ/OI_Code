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
const int MAXM=1E6+10;

vector<int> v[MAXM];
bool vis[MAXM],fafa[MAXN];
int n,a[MAXN],pri[MAXM],f[MAXM],tot;
int mp[MAXM],Ans[MAXN],Ans1[MAXN],Mx;

void sieve()
{
	f[1]=0;
	for(int i=2;i<=Mx;i++)
	{
		if(!vis[i]) pri[++tot]=i,f[i]=1;
		for(int j=1;j<=tot&&i*pri[j]<=Mx;j++)
		{
			vis[i*pri[j]]=1;f[i*pri[j]]=f[i]+1;
			if(!i%pri[j]) break;
		}
	}
	for(int i=1;i<=Mx;i++)
		for(int j=i;j<=Mx;j+=i)
			v[i].push_back(j);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),Mx=max(Mx,a[i]);
	sieve();memset(Ans1,0x3f,sizeof Ans1);
	for(int i=1;i<=n;i++)
	{
		if(!mp[a[i]]) mp[a[i]]=i,fafa[i]=1;
		else Ans[i]=mp[a[i]],Ans1[i]=0;
	}
	memset(mp,0,sizeof mp);
	for(int i=n;i;i--)
	{
		if(fafa[i]&&mp[a[i]]) Ans[i]=mp[a[i]],Ans1[i]=0;
		mp[a[i]]=i;
	}
	memset(mp,0,sizeof mp);
	for(int i=1;i<=n;i++)
		if(!Ans[i]||fafa[i]) 
			mp[a[i]]=i;
	for(int x=1;x<=Mx;x++)
	{
		int mn=1<<30,mnp=0,mn2=1<<30,mnp2=0;
		for(int y:v[x])
			if(mp[y])
			{
				if(f[y]<mn||(f[y]==mn&&mp[y]<mp[mnp])) mn2=mn,mnp2=mnp,mn=f[y],mnp=y;
				else if(f[y]<mn2||(f[y]==mn2&&mp[y]<mp[mnp2])) mn2=f[y],mnp2=y;
			}
		for(int y:v[x])
			if(mp[y])
			{
				if(y==mnp)
				{
					int cur=f[y]+mn2-2*f[x];
					if(cur<Ans1[mp[y]]||(cur==Ans1[mp[y]]&&mp[mnp2]<Ans[mp[y]])) Ans1[mp[y]]=cur,Ans[mp[y]]=mp[mnp2];
				}
				else
				{
					int cur=f[y]+mn-2*f[x];
					if(cur<Ans1[mp[y]]||(cur==Ans1[mp[y]]&&mp[mnp]<Ans[mp[y]])) Ans1[mp[y]]=cur,Ans[mp[y]]=mp[mnp];
				}
			}
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",Ans[i]);
}