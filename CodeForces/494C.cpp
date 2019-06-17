#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXQ=5010;
const int MAXN=1E5+10;

map<pair<int,int>,int> M;
int n,q,a[MAXN],L[MAXQ],R[MAXQ],tot,mx[MAXQ];
double f[MAXQ][MAXQ],nf[MAXQ];
vector<int> T[MAXQ];
vector<double> p[MAXQ];

void dfs(int x)
{
	mx[x]=0;
	sort(T[x].begin(),T[x].end(),[](int x,int y){return L[x]<L[y];});
	for(int v:T[x])
		dfs(v);
	for(int i=L[x],ptr=0;i<=R[x];i++)
	{
		if(ptr<T[x].size()&&i==L[T[x][ptr]])
			i=R[T[x][ptr]],ptr++;
		else
			mx[x]=max(mx[x],a[i]);
	}
	for(int i=0;i<=q;i++)
		f[x][i]=1;
	for(int v:T[x])
	{
		memset(nf,0,sizeof nf);
		int nmx=max(mx[x],mx[v]);
		for(int i=0;i<=q;i++)
		{
			if(i+mx[v]>=nmx&&i+mx[v]-mx[x]>=0&&i+mx[v]-nmx<=q)
				nf[i+mx[v]-nmx]+=(f[v][i]-(i?f[v][i-1]:0))*f[x][min(q,i+mx[v]-mx[x])];
			if(i+mx[x]>=nmx&&i+mx[x]-mx[v]>=1&&i+mx[x]-nmx<=q)
				nf[i+mx[x]-nmx]+=(f[x][i]-(i?f[x][i-1]:0))*f[v][min(q,i+mx[x]-mx[v]-1)];
		}
		f[x][0]=nf[0];
		for(int i=1;i<=q;i++)
			f[x][i]=f[x][i-1]+nf[i];
		mx[x]=nmx;
	}
	for(double pr:p[x])
	{
		memset(nf,0,sizeof nf);
		for(int i=0;i<=q;i++)
			nf[i]+=(1-pr)*(f[x][i]-(i?f[x][i-1]:0)),
			nf[i+1]+=pr*(f[x][i]-(i?f[x][i-1]:0));
		f[x][0]=nf[0];
		for(int i=1;i<=q;i++)
			f[x][i]=f[x][i-1]+nf[i];
	}
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1,l,r;i<=q;i++)
	{
		double p1;
		scanf("%d%d%lf",&l,&r,&p1);
		int cur=M[{l,r}];
		if(!cur)
			M[{l,r}]=cur=++tot,L[tot]=l,R[tot]=r;
		p[cur].push_back(p1);
	}
	if(!M[{1,n}])
		M[{1,n}]=++tot,L[tot]=1,R[tot]=n;
	for(int i=1;i<=tot;i++)
	{
		int mnpos=0;
		for(int j=1;j<=tot;j++)
			if(i!=j&&L[j]<=L[i]&&R[i]<=R[j])
				if(!mnpos||R[mnpos]-L[mnpos]>R[j]-L[j])
					mnpos=j;
		T[mnpos].push_back(i);				
	}
	int  rt=M[{1,n}];
	dfs(rt);
	double Ans=0;
	for(int i=0;i<=q;i++)
		Ans+=(f[rt][i]-(i?f[rt][i-1]:0))*(mx[rt]+i);
	printf("%lf\n",Ans);
}
