#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int INF=1<<30;
const ll INFLL=1ll<<60;

int n,k,a[MAXN];
int curl,curr,cnt[MAXN];
ll cura,f[MAXN],g[MAXN];

void Adjust(int L,int R)
{
	while(curl>L)
		--curl,
		cura+=cnt[a[curl]],
		cnt[a[curl]]++;
	while(curr<R)
		++curr,
		cura+=cnt[a[curr]],
		cnt[a[curr]]++;
	while(curl<L)
		cnt[a[curl]]--,
		cura-=cnt[a[curl]],
		++curl;
	while(curr>R)
		cnt[a[curr]]--,
		cura-=cnt[a[curr]],
		--curr;
}

ll Ask(int l,int r)
{
	Adjust(l,r);
	return cura;
}

void solve(int l,int r,int pl,int pr)
{
	if(l>r)
		return;
	int mid=(l+r)>>1,bst=pl;
	f[mid]=INFLL;
	for(int i=pl;i<=min(pr,mid);i++)
		if(f[mid]>g[i-1]+Ask(i,mid))
			bst=i,f[mid]=g[i-1]+Ask(i,mid);
	solve(l,mid-1,pl,bst);solve(mid+1,r,bst,pr);
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),f[i]=INFLL;
	curl=1;
	while(k--)
	{
		memcpy(g,f,sizeof g);
		solve(1,n,1,n);
	}
	printf("%lld\n",f[n]);
}
