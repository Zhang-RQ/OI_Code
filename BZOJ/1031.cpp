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

const int MAXN=4E5+10;

char s[MAXN];
int tp[MAXN],sa[MAXN],Rank[MAXN],buk[MAXN],n;

void build_sa()
{
	int m=127;
	for(int i=1;i<=n;i++) Rank[i]=s[i],tp[i]=i;
	for(int i=1;i<=m;i++) buk[i]=0;
	for(int i=1;i<=n;i++) buk[Rank[tp[i]]]++;
	for(int i=1;i<=m;i++) buk[i]+=buk[i-1];
	for(int i=n;i;i--) sa[buk[Rank[tp[i]]]--]=tp[i];
	int p=1;
	for(int len=1;p<n;m=p,len<<=1)
	{
		p=0;
		for(int i=n-len+1;i<=n;i++) tp[++p]=i;
		for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
		for(int i=1;i<=m;i++) buk[i]=0;
		for(int i=1;i<=n;i++) buk[Rank[tp[i]]]++;
		for(int i=1;i<=m;i++) buk[i]+=buk[i-1];
		for(int i=n;i;i--) sa[buk[Rank[tp[i]]]--]=tp[i];
		swap(Rank,tp);
		Rank[sa[1]]=p=1;
		for(int i=2;i<=n;i++)
			Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
	}
}

int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	int tn=n;
	for(int i=1;i<n;i++) s[i+n]=s[i];
	n=2*n-1;build_sa();
	for(int i=1;i<=n;i++)
		if(sa[i]+tn-1<=n) putchar(s[sa[i]+tn-1]);
	puts("");
}