#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E4+10;

int n,k,a[MAXN];
int t[MAXN];
int curL=1,curR=0;
ll curs,f[11][MAXN];

void C(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=v;
}

int Q(int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

void adjust(int L,int R)
{
	while(curR<R) curs+=Q(n)-Q(a[curR+1]),C(a[curR+1],1),++curR;
	while(curL>L) curs+=Q(a[curL-1]),C(a[curL-1],1),--curL;
	while(curR>R) C(a[curR],-1),curs-=Q(n)-Q(a[curR]),--curR;
	while(curL<L) C(a[curL],-1),curs-=Q(a[curL]),++curL;
}

void solve(int l,int r,int vl,int vr,ll *f,ll *g)
{
	if(l>r) return;
	int mid=(l+r)>>1,pmid=vl;
	f[mid]=1ll<<60;
	for(int i=vl;i<=min(vr,mid);i++)
	{
		adjust(i,mid);
		if(f[mid]>g[i-1]+curs)
			f[mid]=g[i-1]+curs,pmid=i;
	}
	solve(l,mid-1,vl,pmid,f,g);
	solve(mid+1,r,pmid,vr,f,g);
}

int main()
{
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=k;i++)
		solve(i,n,i,n,f[i],f[i-1]);
	printf("%lld\n",f[k][n]);
}
