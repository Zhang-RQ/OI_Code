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

const int MAXN=15;
const int MAXS=1<<MAXN;
const int MAXM=666;
const int P=1E9+7;
const int inv2=500000004;
const int inv4=250000002;

struct trans_t{
	int s,w;
}trans[MAXN][MAXM];

int n,m,cnt1,cnt2,Cnt[MAXS],ful,tot[MAXN];
map<int,int> f[MAXS];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

inline void add(int S,int w)
{
	for(int i=0;i<n;i++)
		if((S>>i)&1)
		{
			trans[i][++tot[i]].s=S;
			trans[i][tot[i]].w=w;
			break;
		}
}

inline void inc(int &x,int y){x+=y;if(x>P) x-=P;}

int dfs(int S)
{
	int s=S&ful,t=(S>>n)&ful;
	if(s==0&&t==0) return 1;
	if(f[s].count(t)) return f[s][t];
	int ret=0,p=0;
	for(int i=0;i<n;i++) if((s>>i)&1) {p=i;break;}
	for(int i=1;i<=tot[p];i++)
		if((S&trans[p][i].s)==trans[p][i].s)
			inc(ret,1ll*trans[p][i].w*dfs(S^trans[p][i].s)%P);
	return f[s][t]=ret;
}

int main()
{
	assert(1ll*inv2*2%P==1);assert(1ll*inv4*4%P==1);
	scanf("%d%d",&n,&m);ful=(1<<n)-1;
	for(int s=1;s<=ful;s++) Cnt[s]=Cnt[s^(s&(-s))]+1;
	for(int i=1,t,a,b,c,d,s1,s2;i<=m;i++)
	{
		scanf("%d",&t);
		if(t==0)
		{
			scanf("%d%d",&a,&b);
			--a;--b;
			add((1<<a)|(1<<(n+b)),inv2);
		}
		else if(t==1)
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			--a;--b;--c;--d;
			s1=(1<<a)|(1<<(n+b));s2=(1<<c)|(1<<(n+d));
			add(s1,inv2);add(s2,inv2);
			if(s1&s2) continue;
			add(s1|s2,inv4);
		}
		else
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			--a;--b;--c;--d;
			s1=(1<<a)|(1<<(n+b));s2=(1<<c)|(1<<(n+d));
			add(s1,inv2);add(s2,inv2);
			if(s1&s2) continue;
			add(s1|s2,P-inv4);
		}
	}
	printf("%lld\n",1ll*dfs(ful|(ful<<n))*ksm(2,n)%P);
}
