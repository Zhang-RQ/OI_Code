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

const int MAXP=2E7+10;
const int MAXN=5E5+10;

bool vis[MAXP],bg[MAXN];
int pri[MAXP],tot,phi[MAXP],n,m,a[MAXN];
ll t[MAXN];

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

    #if __cplusplus >= 201103L
        template<typename T,typename ...Args>
            inline void read(T& x,Args& ...args)
            {
                read(x);
                read(args...);
            }
    #endif
}

using namespace FastIO;

void init()
{
	phi[1]=1;
	for(int i=2;i<MAXP;i++)
	{
		if(!vis[i]) pri[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&pri[j]*i<MAXP;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) {phi[i*pri[j]]=phi[i]*pri[j];break;}
			else phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
}

ll ksm(ll a,ll b,int p,bool &f)
{
	ll ret=1;
	while(b)
	{
		if(b&1) ret*=a,f|=ret>=p,ret%=p;
		if((a*=a)>=p) f=1,a%=p;
		b>>=1;
	}
	return ret;
}

void add(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=v;
}

ll ask(int x)
{
	ll ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

ll query(int x,int r,int p)
{
	bg[x]=0;
	ll v=ask(x);
	if(v>=p) bg[x]=1,v%=p;
	if(v%p==0) return 0;
	else if(p==1) return 1;
	else if(x==r) return v;
	ll t=query(x+1,r,phi[p]);
	return ksm(v,t+(bg[x+1]?phi[p]:0),p,bg[x]);
}

int main()
{
	init();
	read(n,m);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) add(i,a[i]-a[i-1]);
	for(int i=1,opt,l,r,v;i<=m;i++)
	{
		read(opt,l,r,v);
		if(opt==1) add(l,v),add(r+1,-v);
		else printf("%lld\n",query(l,r,v));
	}
}