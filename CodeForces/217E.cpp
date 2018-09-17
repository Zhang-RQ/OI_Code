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

const int MAXN=3E6+10;

int t[MAXN<<2],ref[MAXN],l[5010],r[5010],k,n;
char s[MAXN],Ans[MAXN];

void build(int x,int l,int r)
{
	t[x]=r-l+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}

void dec(int x,int l,int r,int pos)
{
	--t[x];
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) dec(x<<1,l,mid,pos);
	else dec(x<<1|1,mid+1,r,pos);
}

int kth(int x,int l,int r,int k)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(t[x<<1]>=k) return kth(x<<1,l,mid,k);
	else return kth(x<<1|1,mid+1,r,k-t[x<<1]);
}

int main()
{
	scanf("%s",s+1);
	scanf("%d",&k);scanf("%d",&n);
	build(1,1,k);
	for(int i=1;i<=n;i++) scanf("%d%d",&l[i],&r[i]);
	for(int i=n;i;i--)
		if(r[i]<t[1])
		{
			int len=r[i]-l[i]+1;
			int pos=l[i]+1;
			if(pos>r[i]) pos=l[i];
			for(int j=1;j<=len;j++)
			{
				if(r[i]>=t[1]) break;
				int tps=kth(1,1,k,r[i]+1);
				ref[tps]=kth(1,1,k,pos);
				dec(1,1,k,tps);
				pos+=2;
				if(pos>r[i]) pos=l[i];
			}
		}
	for(int i=1,j=0;i<=k;i++)
		if(ref[i]) Ans[i]=Ans[ref[i]];
		else Ans[i]=s[++j];
	puts(Ans+1);
}