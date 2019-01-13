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

const int MAXN=1E5+10;

int gcd(int a,int b){return b?gcd(b,a%b):a;}

bool vis[MAXN];
int pos[MAXN],c[MAXN],n,s,q,p,m,d,cnt[MAXN],id[MAXN];
set<int> st;
set<pair<int,int> > st2[MAXN];

void solve()
{
	int Ans=0;
	st.clear();memset(vis,0,sizeof vis);
	scanf("%d%d%d%d%d%d",&n,&s,&q,&p,&m,&d);
	pos[0]=s;
	for(int i=1;i<n;i++) c[i]=(1ll*c[i-1]*q+p)%m;
	int k=gcd(n,d);
	for(int i=0;i<k;i++)
	{
		int x=i,t=0;
		do{
			id[x]=++t;
			if(x!=s)  ++cnt[i],st2[i].insert({t,x});
			(x+=d)%=n;
		}while(x!=i);
	}
	for(int i=0;i<k;i++) if(cnt[i]) st.insert(i);
	for(int i=1;i<n;i++) c[i]%=n;
	for(int i=1;i<n;i++)
	{
		int l=c[i]%k,_l=l;
		if(!cnt[l])
		{
			auto it=st.lower_bound(l);
			if(it!=st.end()) l=*it;
			else l=*st.begin();
		}
		int o=c[i]+(l-_l+k)%k;
		auto it=st2[l].lower_bound(make_pair(id[o],o));
		if(it!=st2[l].end()) pos[i]=it->second,st2[l].erase(it);
		else
		{
			pos[i]=st2[l].begin()->second;
			st2[l].erase(st2[l].begin());
		}
		if(!--cnt[l]) st.erase(l);
	}
	for(int i=0;i<n;i++)
		if(!vis[i])
		{
			int x=i,l=0;
			vis[i]=1;
			do vis[x=pos[x]]=1,++l; while(x!=i);
			if(l>1) Ans+=i?l+1:l-1;
		}
	printf("%d\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}