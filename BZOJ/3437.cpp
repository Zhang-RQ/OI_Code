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

const int MAXN=1E6+10;

#define X(i) s1[i]
#define Y(i) (f[i]+s2[i])

int n,q[MAXN],head,tail;
ll a[MAXN],s1[MAXN],s2[MAXN],f[MAXN];

inline double slope(int i,int j){return (1.0*Y(j)-Y(i))/(X(j)-X(i));}

int main()
{
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1,x;i<=n;i++) read(x),s1[i]=s1[i-1]+x,s2[i]=s2[i-1]+1ll*x*i;
    q[head=tail=1]=0;
	for(int i=1;i<=n;i++)
	{
        while(head<tail&&slope(q[head],q[head+1])<=i) ++head;
        f[i]=-i*X(q[head])+Y(q[head])+i*s1[i]-s2[i]+a[i];
        while(head<tail&&slope(q[tail-1],q[tail])>=slope(q[tail-1],i)) --tail;
        q[++tail]=i;
	}
	printf("%lld\n",f[n]);
}