#include<bits/stdc++.h>

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

const int MAXN=2E5+10;
const int MAXM=MAXN*42;

int ans1,ans2;
int n,m,tot;
int rt[MAXN],ch[MAXM][2],E[MAXM];
vector<int> T[MAXN];

int Min(int a,int b){if(!a||!b) return a|b;return min(a,b);}

void ins(int &p,int d,int v,int x=19)
{
    if(!p) p=++tot;
	if(x<0) return E[p]=Min(E[p],v),void();
    int now=d>>x&1;
	ins(ch[p][now],d,v,x-1);
}

int ask(int p,int d,int x=19)
{
    if(x<0) return ans2=E[p],0;
	int now=d>>x&1;
    return ch[p][!now]?ask(ch[p][!now],d,x-1)+(1<<x):ask(ch[p][now],d,x-1);
}

int merge(int x,int y)
{
    if(!x||!y) return x|y;
    int p=++tot;
	E[p]=Min(E[x],E[y]);
    for(int i=0;i<2;i++)
        ch[p][i]=merge(ch[x][i],ch[y][i]);
    return p;
}
void dfs(int x,int fa)
{
    for(int v:T[x])
		if(v!=fa)
			dfs(v,x),rt[x]=merge(rt[x],rt[v]);
}
void solve()
{
	read(n,m);
	for(int i=1;i<=n;i++)
		T[i].clear();
    for(int i=1;i<=tot;i++)
        ch[i][0]=ch[i][1]=E[i]=0;
	tot=0;
    for(int x,i=1;i<=n;i++)
		rt[i]=0,read(x),ins(rt[i],x,i);
    for(int x,y,i=1;i<n;i++)
		read(x,y),T[x].push_back(y),T[y].push_back(x);
    dfs(1,0);ans1=ans2=0;
    while(m--){
        int a,b;
		read(a,b);
        a^=ans2;b^=ans1;
        ans1=ask(rt[a],b);
        printf("%d %d\n",ans2,ans1);
    }
}

int main()
{
	int T;
	for(read(T);T--;solve());
}
