%:pragma GCC optimize(2)
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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
namespace FastIO
{
	const int Bufsiz=1<<22;	// buffer size
	inline char get_c() {
		static char buf[Bufsiz];	// buffer
		static char *head = buf + Bufsiz;
		static char *tail = buf + Bufsiz;
		if (head == tail)	// at the end of buffer
			tail = buf + fread(head = buf, 1, BUFSIZ, stdin);	// reload from STDIN
		return *head++;
	}
	inline int get_i() {
		int res = 0;	// result
		int isn = 0; 	// is negative
		int chr = get_c();	// current char
		for (; chr < 48; chr = get_c())
			if (chr == '-')isn ^= 1;
		for (; chr > 47; chr = get_c())
			res = res * 10 + chr - 48;
		return isn ? -res : res;
	}
}
const int MAXN=50100;
const int MAXM=100010;
const int INF=1<<30;
int fa[MAXM],mp[MAXM],w[MAXM],siz[MAXN];
ll ans[MAXM];
struct Edge{
    int u,v,w,id;
    inline bool operator <(const Edge &rhs)const{return w<rhs.w;}
}gra[25][MAXM],d[MAXM],t[MAXM];
struct node{
    int num,val;
}qus[MAXM];
inline int find(int x) {return x==fa[x]?x:x=find(fa[x]);}
inline void merge(int x,int y)
{
	x=find(x);y=find(y);
	if(siz[x]<siz[y]) swap(x,y);
	fa[y]=x,siz[x]+=siz[y];
}
inline void reset(int _n,const Edge *ed) {for(int i=1;i<=_n;i++) fa[ed[i].u]=ed[i].u,fa[ed[i].v]=ed[i].v,siz[ed[i].u]=1,siz[ed[i].v]=1;}
inline ll contraction(int &n)
{
    int cnt=0;
    sort(d+1,d+1+n);
    for(int i=1;i<=n;i++)
    {
        if(find(d[i].u)!=find(d[i].v))
        {
            merge(d[i].u,d[i].v);
            t[++cnt]=d[i];
        }
    }
    reset(cnt,t);
    ll ret=0;
    for(int i=1;i<=cnt;i++)
    {
        if(t[i].w!=-INF&&find(t[i].u)!=find(t[i].v))
        {
			merge(t[i].u,t[i].v);
            ret+=t[i].w;
        }
    }
    cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(find(d[i].u)!=find(d[i].v))
        {
            t[++cnt]=d[i];
            t[cnt].u=find(d[i].u);
            t[cnt].v=find(d[i].v);
            mp[d[i].id]=cnt;
        }
    }
    reset(n,d);
    for(int i=1;i<=cnt;i++)
        d[i]=t[i];
    n=cnt;
    return ret;
}
inline void reduction(int &n)
{
    int cnt=0;
    sort(d+1,d+1+n);
    for(int i=1;i<=n;i++)
    {
        if(find(d[i].u)!=find(d[i].v))
        {
			merge(d[i].u,d[i].v);
            t[++cnt]=d[i];
            mp[d[i].id]=cnt;
        }
        else if(d[i].w==INF)
        {
            t[++cnt]=d[i];
            mp[d[i].id]=cnt;
        }
    }
    reset(n,d);
    for(int i=1;i<=cnt;i++) d[i]=t[i];
    n=cnt;
}
void CDQ(int lvl,int n,int L,int R,ll tans)
{
    if(L==R) w[qus[L].num]=qus[L].val;
    for(int i=1;i<=n;i++)
    {
        gra[lvl][i].w=w[gra[lvl][i].id];
        d[i]=gra[lvl][i];
        mp[d[i].id]=i;
    }
    if(L==R)
    {
        ans[L]=tans;
        sort(d+1,d+1+n);
        for(int i=1;i<=n;i++)
        {
            if(find(d[i].u)!=find(d[i].v))
            {
				merge(d[i].u,d[i].v);
                ans[L]+=d[i].w;
            }
        }
        reset(n,d);
        return;
    }
    for(int i=L;i<=R;i++)
        d[mp[qus[i].num]].w=-INF;
    tans+=contraction(n);
    for(int i=L;i<=R;i++)
        d[mp[qus[i].num]].w=INF;
    reduction(n);
    for(int i=1;i<=n;i++)
        gra[lvl+1][i]=d[i];
    int mid=(L+R)>>1;
    // printf("%d %d %d %d %lld\n",lvl,L,R,n,tans);
    CDQ(lvl+1,n,L,mid,tans);
    CDQ(lvl+1,n,mid+1,R,tans);
}
int n,m,q;
int main()
{
	// freopen("E:\\test_environment\\data.in","r",stdin);
    using namespace FastIO;
    n=get_i();m=get_i();q=get_i();
    // printf("%d %d %d\n",n,m,q);
    for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
    for(int i=1;i<=m;i++)
        gra[1][i].u=get_i(),gra[1][i].v=get_i(),gra[1][i].w=get_i(),w[i]=gra[1][i].w,gra[1][i].id=i;
    for(int i=1;i<=q;i++)
        qus[i].num=get_i(),qus[i].val=get_i();
    CDQ(1,m,1,q,0);
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
