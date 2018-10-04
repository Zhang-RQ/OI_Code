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

const int P=1E9+7;
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

bool vis[MAXM];
int pri[MAXM],mindiv[MAXM],tot;
ll f[MAXM][21],ts[21];

void init()
{
	f[0][0]=1;
	for(int i=1;i<=20;i++) f[0][i]=2;
	for(int i=1;i<MAXM;i++)
	{
		ts[0]=f[i-1][0];
		f[i][0]=1;
		for(int j=1;j<=20;j++)
			(ts[j]=ts[j-1]+f[i-1][j])%=P;
		for(int j=1;j<=20;j++)
			f[i][j]=ts[j];
	}
	for(int i=2;i<MAXM;i++)
	{
		if(!vis[i]) pri[++tot]=i,mindiv[i]=i;
		for(int j=1;j<=tot&&pri[j]*i<MAXM;j++)
		{
			vis[i*pri[j]]=1;mindiv[i*pri[j]]=pri[j];
			if(i%pri[j]==0) break;
		}
	}
}

ll query(int x,int r)
{
	ll ret=1;
	while(x!=1)
	{
		int cnt=0,tx=x;
		while(x%mindiv[tx]==0) cnt++,x/=mindiv[tx];
		(ret*=f[r][cnt])%=P;
	}
	return ret;
}

int main()
{
	init();int q,n,r;
	read(q);
	while(q--)
		read(r,n),printf("%lld\n",query(n,r));
}