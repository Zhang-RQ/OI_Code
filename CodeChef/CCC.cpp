#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1010;
const int INF=1<<30;
const ll INFLL=1ll<<60;

int a[MAXN],n,z,stk[MAXN];
ll f[MAXN][MAXN];

ll get_best(int D,int lim,int k)
{
	int l=1,r=lim;
	while(r-l>3)
	{
		int mid1=(l+l+r)/3,mid2=(l+r+r)/3;
		if(f[D][stk[mid1]]-1ll*k*stk[mid1]<f[D][stk[mid2]]-1ll*k*stk[mid2])
			r=mid2;
		else
			l=mid1;
	}
	ll ret=INFLL;
	for(int i=l;i<=r;i++)
		ret=min(ret,f[D][stk[i]]-1ll*k*stk[i]);
	return ret;
}

void solve()
{
	scanf("%d%d",&n,&z);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<=z;i++)
		for(int j=0;j<=n;j++)
			f[i][j]=INF;
	sort(a+1,a+1+n,greater<int>());
	f[0][0]=0;
	for(int j=1;j<=z;j++)
	{
		int top=1;stk[top]=0;
		for(int i=1;i<=n;i++)
		{
			f[j][i]=get_best(j-1,top,a[i])+1ll*i*a[i];
			while(top>1&&(f[j-1][stk[top]]-f[j-1][stk[top-1]])*(i-stk[top-1])>=(f[j-1][i]-f[j-1][stk[top-1]])*(stk[top]-stk[top-1]))
				--top;
			stk[++top]=i;
		}
	}
	ll Ans=INFLL;
	for(int i=1;i<=n;i++)
		Ans=min(Ans,f[z][i]);
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
