#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const double EPS=1E-8;

int n,q[MAXN];
ll s[MAXN],f[MAXN],h[MAXN];
pair<int,int> a[MAXN],b[MAXN],c[MAXN];

ll X(int i){return h[i];}

ll Y(int i){return f[i]+1ll*h[i]*h[i]-s[i];}

double slope(int i,int j){return 1.0*(Y(j)-Y(i))/(X(j)-X(i)+EPS);}

void solve(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid);
	for(int i=l;i<=r;i++)
		b[i]=a[i],c[i]=a[i];
	sort(b+l,b+mid+1);
	sort(c+mid+1,c+r+1);
	int hd=1,tl=0;
	for(int i=l;i<=mid;i++)
	{
		while(hd<tl&&slope(q[tl-1],q[tl])>=slope(q[tl-1],b[i].second)) --tl;
		q[++tl]=b[i].second;
	}
	for(int i=mid+1;i<=r;i++)
	{
		int now=c[i].second;
		while(hd<tl&&slope(q[hd],q[hd+1])<=2*h[now]) ++hd;
		f[now]=min(f[now],Y(q[hd])-2*h[now]*X(q[hd])+s[now-1]+1ll*h[now]*h[now]);
	}
	solve(mid+1,r);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&h[i]);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),s[i]=s[i-1]+x;
	for(int i=1;i<=n;i++)
		a[i].first=h[i],a[i].second=i;
	memset(f,0x3f,sizeof f);
	f[1]=0;
	solve(1,n);
	printf("%lld\n",f[n]);
}
