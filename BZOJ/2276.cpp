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

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
        	bool f=0;
            x=0;static char ch=get_char();
            while(!isdigit(ch)) f|=ch=='-',ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
            if(f) x=-x;
        }
}

using namespace FastIO;
using namespace std;

const int MAXN=1E6+10;

int n,L[MAXN],R[MAXN],Ans;
deque<int> q;

int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(L[i]),read(R[i]);
	int lst=0;
	for(int i=1;i<=n;i++)
	{
		while(q.size()&&L[q.front()]>R[i]) lst=q.front(),q.pop_front();
		Ans=max(Ans,i-lst);
		while(q.size()&&L[q.back()]<=L[i]) q.pop_back();
		q.push_back(i);
	}
	printf("%d\n",Ans);
}