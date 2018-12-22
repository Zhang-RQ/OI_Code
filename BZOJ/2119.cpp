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

const int MAXN=2E5+10;

int n,m,lg2[MAXN],a[MAXN],v[MAXN],b[MAXN];
ll Ans=0;

struct Suffix_Array{
	int Rank[MAXN],sa[MAXN],tp[MAXN],buk[MAXN],he[MAXN],st[MAXN][19];

	void build(int *s,int n)
	{
		int m=n;
		for(int i=1;i<=n;i++) Rank[i]=s[i],tp[i]=i;
		for(int i=1;i<=m;i++) buk[i]=0;
		for(int i=1;i<=n;i++) buk[Rank[tp[i]]]++;
		for(int i=1;i<=m;i++) buk[i]+=buk[i-1];
		for(int i=n;i;i--) sa[buk[Rank[tp[i]]]--]=tp[i];
		int p=1;
		for(int len=1;p<n;len<<=1,m=p)
		{
			p=0;
			for(int i=n-len+1;i<=n;i++) tp[++p]=i;
			for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
			for(int i=1;i<=m;i++) buk[i]=0;
			for(int i=1;i<=n;i++) buk[Rank[tp[i]]]++;
			for(int i=1;i<=m;i++) buk[i]+=buk[i-1];
			for(int i=n;i;i--) sa[buk[Rank[tp[i]]]--]=tp[i];
			swap(Rank,tp);Rank[sa[1]]=p=1;
			for(int i=2;i<=n;i++)
				Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
		}
		for(int i=1,lst=0;i<=n;he[Rank[i++]]=lst)
			for(lst=lst?lst-1:lst;s[i+lst]==s[sa[Rank[i]-1]+lst];++lst);
		if(!lg2[2]) for(int i=2;i<=n;i++) lg2[i]=lg2[i>>1]+1;
		for(int i=1;i<=n;i++) st[i][0]=he[i];
		for(int j=1;j<=lg2[n];j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}

	int LCP(int x,int y) //pos
	{
		x=Rank[x];y=Rank[y];
		if(x>y) swap(x,y);
		++x;
		int len=lg2[y-x+1];
		return min(st[x][len],st[y-(1<<len)+1][len]);
	}
}S,T;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=2;i<=n;i++) v[i-1]=a[i]-a[i-1];
	n--;sort(v+1,v+1+n);
	int tot=unique(v+1,v+1+n)-v-1;
	for(int i=1;i<=n;i++) b[i]=lower_bound(v+1,v+1+tot,a[i+1]-a[i])-v;
	S.build(b,n);
	reverse(b+1,b+1+n);
	T.build(b,n);
	reverse(b+1,b+1+n);
	for(int len=1;len<=n;len++)
	{
		for(int i=1;i<=n;i+=len)
		{
			int p=i-len-m;
			if(2*len+m>n||p<=0||b[p]!=b[i]) continue;
			int L1=min(S.LCP(p,i),len),L2=min(T.LCP(n-p+1,n-i+1),len);
			int l=0;
			if(L1&&L2) l=L1+L2-1;
			else len=L1+L2;
			if(l>=len) Ans+=l-len+1;
		}
	}
	printf("%lld\n",Ans);
}