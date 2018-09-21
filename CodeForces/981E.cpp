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
#include<bitset>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=10010;

int n,q;
vector<int> tag[MAXN<<2];
bitset<MAXN> Ans,Res,t[MAXN<<2];

void insert(int x,int l,int r,int cl,int cr,int v)
{
	if(cl<=l&&r<=cr) return tag[x].push_back(v);
	int mid=(l+r)>>1;
	if(cl<=mid) insert(x<<1,l,mid,cl,cr,v);
	if(cr>mid)  insert(x<<1|1,mid+1,r,cl,cr,v);
}

void dfs(int x,int l,int r,bitset<MAXN> lst)
{
	for(int p:tag[x])
		lst|=lst<<p;
	if(l==r)
		return Ans|=lst,void();
	int mid=(l+r)>>1;
	t[x]=lst;
	dfs(x<<1,l,mid,t[x]);
	dfs(x<<1|1,mid+1,r,t[x]);
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1,l,r,x;i<=q;i++) scanf("%d%d%d",&l,&r,&x),insert(1,1,n,l,r,x);
	Res[0]=1;
	dfs(1,1,n,Res);
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=Ans[i];
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++)
		if(Ans[i])
			printf("%d ",i);
	puts("");
}