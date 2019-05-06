#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

struct FastIO{
    static const int S=1e7;
    int wpos;
    char wbuf[S];
    FastIO():wpos(0){}

    inline int xchar()
    {
        static char buf[S];
        static int len=0,pos=0;
        if(pos==len)
            pos=0,len=fread(buf,1,S,stdin);
        return buf[pos++];
    }

    inline int operator () ()
    {
        int c=xchar(),x=0,ng=0;
        while (!isdigit(c)) ng|=(c=='-'),c=xchar();
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline ll operator ! ()
    {
        int c=xchar(),ng=0;ll x=0;
        while(!isdigit(c)) ng|=(c=='-'),c=xchar();
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline void wchar(int x)
    {
        if(wpos==S) fwrite(wbuf,1,S,stdout),wpos=0;
        wbuf[wpos++]=x;
    }

    inline void operator () (ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar('\n');
    }

    inline void space(ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar(' ');
    }

    inline void nextline() {wchar('\n');}

    ~FastIO() {if(wpos) fwrite(wbuf,1,wpos,stdout),wpos=0;}
}io;

const int MAXN=5E5+10;
const int MAXM=2E6+10;

int cnt_a,inf_a,fa[MAXM],dep[MAXM],inT[MAXM];
int to[MAXM],to2[MAXM],cnt_e=1,n,m,k,x[MAXN],y[MAXN],rk[MAXM],vis[MAXM];
ll Sp[MAXM],f[MAXM],g[MAXM];
double slp[MAXM];
vector<int> out[MAXN],T[MAXM];
map<int,int> M[MAXN];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

ll crs(int u,int v){return 1ll*y[v]*x[u]-1ll*y[u]*x[v];}

void add(int u,int v)
{
	//u -> v
	++cnt_e;to[cnt_e]=v;M[u][v]=cnt_e;
	slp[cnt_e]=atan2(y[v]-y[u],x[v]-x[u]);
	if(slp[cnt_e]<0) slp[cnt_e]+=233;
	out[u].push_back(cnt_e);
}

void dfs(int x,int fa)
{
	f[x]=Sp[x];
	g[x]=Sp[x]*Sp[x];
	dep[x]=dep[fa]+1;
	for(int v:T[x])
		if(v!=fa)
			dfs(v,x),
			f[x]+=f[v],
			g[x]+=g[v];
}

int main()
{
	n=io();m=io();k=io();
	for(int i=1;i<=n;i++)
		x[i]=io(),y[i]=io();
	for(int i=1,a,b;i<=m;i++)
	{
		a=io();b=io();
		add(a,b);add(b,a);
	}
	for(int i=1;i<=n;i++)
		sort(out[i].begin(),out[i].end(),[](int a,int b){return slp[a]<slp[b];});
	for(int i=1;i<=n;i++)
		for(size_t _=0;_<out[i].size();_++)
			rk[out[i][_]]=_;
	for(int i=2;i<=cnt_e;i++)
		if(!vis[i])
		{
			int x=to[i^1],nowe=i;
			ll S=0;++cnt_a;
			while(1)
			{
				if(vis[nowe]) break; 
				to2[nowe]=cnt_a;
				S+=crs(x,to[nowe]);
				x=to[nowe];vis[nowe]=1;
				nowe=rk[nowe^1]?out[x][rk[nowe^1]-1]:out[x].back();
			}
			Sp[cnt_a]=S;
			if(S<0) inf_a=cnt_a;
		}
	for(int i=1;i<=cnt_a;i++)
		fa[i]=i;
	for(int i=2;i<=cnt_e;i+=2)
	{
		int U=to2[i],V=to2[i^1];
		if(find(U)!=find(V))
			T[U].push_back(V),
			T[V].push_back(U),
			fa[find(U)]=find(V),
			inT[i]=inT[i^1]=1;
	}
	dfs(inf_a,0);
	ll lstans=0;
	for(int i=1,c,lst,p,beg;i<=k;i++)
	{
		ll ans1=0,ans2=0;
		c=(io()+lstans)%n+1;
		lst=(io()+lstans)%n+1;
		beg=lst;
		while(c--)
		{
			if(c==0) p=beg;
			else p=(io()+lstans)%n+1;
			int id=M[lst][p];
			if(inT[id])
			{
				int U=to2[id^1],V=to2[id];
				if(dep[V]>dep[U])
					ans1+=g[V],ans2+=f[V];
				else
					ans1-=g[U],ans2-=f[U];
			}
			lst=p;
		}
		ans2<<=1;
		ll d=__gcd(ans1,ans2);
		ans1/=d;ans2/=d;
		io.space(lstans=ans1);io(ans2);
	}
}
