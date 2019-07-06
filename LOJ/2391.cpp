#include<bits/stdc++.h>

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

const int MAXN=2E6+10;
const int P=1E9+7;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

struct DSU{
	int fa[MAXN];

	int& operator [] (int x){return fa[x];}
	
	int find(int x)
	{
		return x==fa[x]?x:fa[x]=find(fa[x]);
	}

	int operator () (int x){return find(x);}

	void merge(int x,int y)
	{
		x=find(x);y=find(y);
		if(x==y)
			return;
		fa[x]=y;
	}
}Fa,Nxt;

int jmp[MAXN],n,tp[MAXN],id[MAXN];
int pos[MAXN],pnts[MAXN],tot;

void Merge(int x,int y)
{
	if(Fa(x)==Fa(y))
		puts("0"),exit(0);
	if(Fa(x+n)==Fa(y+n))
		puts("0"),exit(0);
	Fa.merge(x,y+n);Fa.merge(y,x+n);
}

int main()
{
	read(n);
	for(int i=1,l,r;i<=n;i++)
	{
		read(l,r);
		tp[l]=1,tp[r]=2;
		id[l]=id[r]=i;
	}
	int lim=n<<1;
	for(int i=1;i<=lim;i++)
	{
		Fa[i]=i;jmp[i]=i+1;
		if(tp[i]==1)
			Nxt[i]=i;
		else
			Nxt[i]=i+1;
	}
	Nxt[lim+1]=lim+1;
	for(int i=1;i<=lim;i++)
	{
		if(tp[i]==1)
			jmp[i]=i+1,pos[id[i]]=i;
		else
		{
			tot=0;
			for(int t=Nxt(pos[id[i]]+1);t<=i;t=Nxt(jmp[t]))
			{
				pnts[++tot]=t;
				Merge(id[i],id[t]);
			}
			Nxt[pos[id[i]]]=pos[id[i]]+1;
			for(int j=1;j<=tot;j++)
				jmp[pnts[j]]=i+1;
		}
	}
	int tot=0;
	for(int i=1;i<=lim;i++)
		tot+=Fa(i)==i;
	tot>>=1;
	printf("%lld\n",ksm(2,tot));
}
