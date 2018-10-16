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

const int MAXN=1E6+10;
const int MAXM=1E6+10;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
            x=0;static char ch=get_char();
            while(!isdigit(ch)) ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
        }
}

using namespace FastIO;

struct __edge{
	int v,nxt;
}Edge[MAXM<<1];

int head[MAXN],cnt_e,d[MAXN],rt1,rt2;
int m[MAXN],n,g;
ll Ans,L[MAXN],R[MAXN],k;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	if(fa!=0)
	{
		if(L[fa]==0) L[x]=R[x]=0;
		else if(d[x]>1)
		{
			L[x]=L[fa]*(d[x]-1);
			R[x]=(R[fa]+1)*(d[x]-1)-1;
			if(L[x]>1E9) L[x]=R[x]=0;
		}
		else L[x]=L[fa],R[x]=R[fa];
	}
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);
	}
}

int main()
{
	read(n);read(g);read(k);
	for(int i=1;i<=g;i++) read(m[i]),assert(m[i]!=0);
	sort(m+1,m+1+g);
	for(int i=1,u,v;i<n;i++)
	{
		read(u);read(v);++d[u];++d[v];
		if(i!=1) add(u,v),add(v,u);
		else rt1=u,rt2=v;
	}
	if(d[rt1]>1) L[rt1]=1ll*k*(d[rt1]-1),R[rt1]=1ll*(k+1)*(d[rt1]-1)-1;
	else L[rt1]=R[rt1]=k;
	if(d[rt2]>1) L[rt2]=1ll*k*(d[rt2]-1),R[rt2]=1ll*(k+1)*(d[rt2]-1)-1;
	else L[rt2]=R[rt2]=k;
	dfs(rt1,0);dfs(rt2,0);
	for(int i=1;i<=n;i++)
		if(d[i]==1)
			Ans+=1ll*(upper_bound(m+1,m+1+g,R[i])-lower_bound(m+1,m+1+g,L[i]))*k;
	printf("%lld\n",Ans);
}