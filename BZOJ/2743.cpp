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

const int MAXN=2E6+10;

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

struct Query{
	int l,r,id;
	bool operator < (const Query &rhs) const {return r<rhs.r;}
}q[MAXN];

int t[MAXN],n,c,m,lst[MAXN],a[MAXN],Ans[MAXN],pre[MAXN];

void add(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=v;
}

int query(int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

void insert(int x) {add(pre[pre[x]]+1,1);add(pre[x]+1,-1);}

int main()
{
	read(n);read(c);read(m);
	for(int i=1;i<=n;i++) read(a[i]),pre[i]=lst[a[i]],lst[a[i]]=i;
	for(int i=1;i<=m;i++) read(q[i].l),read(q[i].r),q[i].id=i;
	sort(q+1,q+1+m);
	int cur=0;
	for(int i=1;i<=m;i++)
	{
		while(cur+1<=q[i].r)
			insert(++cur);
		Ans[q[i].id]=query(q[i].l);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",Ans[i]);
}