#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXV=2E5;
const int MAXN=4E5+10;

int vis[MAXN];
int pr[MAXN],pc,cnt,id[MAXN],npc;
ull g[MAXN];
ll n,pos[MAXN],k;

int ID(ll x){return x<=MAXV?id[x]:id[MAXN-n/x];}

void sieve()
{
	for(int i=2;i<=MAXV;i++)
	{
		if(!vis[i]) pr[++pc]=i;
		for(int j=1;j<=pc&&i*pr[j]<=MAXV;j++)
		{
			vis[i*pr[j]]=1;
			if(!(i%pr[j])) break;
		}
	}
}

ull S(int i,int j)
{
	ll p=pos[i];
	ull Ret=(k+1)*(g[i]-j+1);
	if(j>npc) return Ret;
	for(int l=j;l<=npc&&1ll*pr[l]*pr[l]<=p;l++)
	{
		ll pw=pr[l];
		for(int e=1;pw*pr[l]<=p;e++,pw*=pr[l])
			Ret+=S(ID(p/pw),l+1)*(e*k+1)+(k*(e+1)+1);
	}
	return Ret;
}

void solve()
{
	cnt=0;
	scanf("%lld%lld",&n,&k);
	npc=upper_bound(pr+1,pr+1+pc,(int)(sqrt(n)))-pr-1;
	for(ll i=1,nxt=0;i<=n;i=nxt+1)
		pos[++cnt]=n/i,nxt=n/(n/i);
	reverse(pos+1,pos+1+cnt);
	for(int i=1;i<=cnt;i++)
		g[i]=pos[i]-1,id[pos[i]<=MAXV?pos[i]:MAXN-n/pos[i]]=i;
	for(int j=1;j<=npc;j++)
		for(int i=cnt;i;i--)
			if(1ll*pr[j]*pr[j]<=pos[i])
				g[i]-=g[ID(pos[i]/pr[j])]-j+1;
			else
				break;
	printf("%llu\n",S(cnt,1)+1);
}

int main()
{
	int T;
	for(scanf("%d",&T),sieve();T--;solve());
}
