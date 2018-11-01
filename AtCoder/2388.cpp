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

int n,a[MAXN],b[MAXN],fa[MAXN],siz[MAXN],s1,s2,c[MAXN],d[MAXN];
int Ans=0;
bool ban[MAXN];
map<int,int> mp;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),s1^=a[i];
	for(int i=1;i<=n;i++) scanf("%d",&b[i]),s2^=b[i];
	for(int i=1;i<=n+1;i++) fa[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++) ban[i]=a[i]==b[i];
	a[++n]=s1;b[n]=s2;
	for(int i=1;i<=n;i++)
		c[i]=a[i],d[i]=b[i];
	sort(c+1,c+1+n);sort(d+1,d+1+n);
	for(int i=1;i<=n;i++)
		if(c[i]!=d[i])
			return puts("-1"),0;
	for(int i=1;i<=n;i++)
	{
		if(ban[i]) continue;
		if(mp[a[i]]) fa[i]=fa[mp[a[i]]],siz[mp[a[i]]]++;
		else mp[a[i]]=i;
	}
	for(int i=1;i<=n-1;i++)
	{
		if(ban[i]) continue;
		int x=find(i),y=find(mp[b[i]]);
		if(x!=y)  fa[x]=y,siz[y]+=siz[x];
	}
	for(int i=1;i<=n;i++)
	{
		if(ban[i]) continue;
		if(fa[i]==i)
		{
			Ans+=siz[i];
			if(find(n)!=i) Ans++;
			else Ans--;
		}
	}
	printf("%d\n",Ans);
}