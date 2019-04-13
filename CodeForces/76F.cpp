#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int INF=1<<30;

struct OPT{
	int x,s1,s2,id;
}op[MAXN],tL[MAXN],tR[MAXN];

pair<int,int> p[MAXN];

int n,V,t[MAXN],Ans1[MAXN],Ans2[MAXN];
ll v1[MAXN],v2[MAXN],totv1,totv2,val1[MAXN],val2[MAXN];

void C(int x,int v) //suffix BIT
{
	for(;x;x-=x&(-x))
		t[x]=max(t[x],v);
}

int Q(int x)
{
	int ret=-INF;
	for(;x<=n+1;x+=x&(-x))
		ret=max(ret,t[x]);
	return ret;
}

void Cls(int x)
{
	for(;x;x-=x&(-x))
		t[x]=-INF;
}

void solve(int l,int r,int *F)
{
	if(l==r) return;
	int mid=(l+r)>>1,totl=mid-l+1,totr=r-mid;
	solve(l,mid,F);
	for(int i=l;i<=mid;i++)
		tL[i-l+1]=op[i];
	for(int i=mid+1;i<=r;i++)
		tR[i-mid]=op[i];
	sort(tL+1,tL+1+totl,[](const OPT &Lhs,const OPT &Rhs){return Lhs.x<Rhs.x;});
	sort(tR+1,tR+1+totr,[](const OPT &Lhs,const OPT &Rhs){return Lhs.x<Rhs.x;});
	int ptrL=1,ptrR=1;
	while(ptrL<=totl&&ptrR<=totr)
	{
		if(tL[ptrL].x<=tR[ptrR].x)
			C(tL[ptrL].s1,F[tL[ptrL].id]),++ptrL;
		else
			F[tR[ptrR].id]=max(F[tR[ptrR].id],Q(tR[ptrR].s1)+1),++ptrR;
	}
	while(ptrR<=totr)
		F[tR[ptrR].id]=max(F[tR[ptrR].id],Q(tR[ptrR].s1)+1),++ptrR;
	for(int i=1;i<=totl;i++)
		Cls(tL[i].s1);
	ptrL=totl;ptrR=totr;
	while(ptrL&&ptrR)
	{
		if(tL[ptrL].x>=tR[ptrR].x)
			C(tL[ptrL].s2,F[tL[ptrL].id]),--ptrL;
		else
			F[tR[ptrR].id]=max(F[tR[ptrR].id],Q(tR[ptrR].s2)+1),--ptrR;
	}
	while(ptrR)
		F[tR[ptrR].id]=max(F[tR[ptrR].id],Q(tR[ptrR].s2)+1),--ptrR;
	for(int i=1;i<=totl;i++)
		Cls(tL[i].s2);
	solve(mid+1,r,F);
}

int main()
{
	memset(Ans1,0xcf,sizeof Ans1);
	memset(Ans2,0xcf,sizeof Ans2);
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
		Cls(i);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].second,&p[i].first);
	scanf("%d",&V);
	sort(p+1,p+1+n);
	for(int i=0;i<=n;i++)
		v1[++totv1]=val1[i]=p[i].second-1ll*V*p[i].first,
		v2[++totv2]=val2[i]=-p[i].second-1ll*V*p[i].first;
	sort(v1+1,v1+1+totv1);
	sort(v2+1,v2+1+totv2);
	totv1=unique(v1+1,v1+1+totv1)-v1-1;
	totv2=unique(v2+1,v2+1+totv2)-v2-1;
	for(int i=0;i<=n;i++)
		val1[i]=lower_bound(v1+1,v1+1+totv1,val1[i])-v1,
		val2[i]=lower_bound(v2+1,v2+1+totv2,val2[i])-v2;
	for(int i=0;i<=n;i++)
		op[i]=(OPT){p[i].second,(int)val1[i],(int)val2[i],i};
	Ans1[0]=Ans2[0]=0;
	solve(0,n,Ans1);
	sort(op,op+n+1,[](const OPT &Lhs,const OPT &Rhs){return Lhs.id<Rhs.id;});
	for(int i=1;i<=n;i++)
		Ans2[i]=1;
	solve(0,n,Ans2);
	int ans1=0,ans2=0;
	for(int i=0;i<=n;i++)
		ans1=max(ans1,Ans1[i]),
		ans2=max(ans2,Ans2[i]);
	printf("%d %d\n",ans1,ans2);
}
