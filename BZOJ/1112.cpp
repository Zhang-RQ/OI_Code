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

const int MAXN=1E5+10;

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

struct node{
	int l,r,siz;
	ll sum;
}t[(MAXN<<5)+(MAXN<<4)];

int cnt,n,k,rt[MAXN],a[MAXN],mx;
ll Ans=1ll<<60;

void insert(int &x,int l,int r,int pos,int y)
{
	x=++cnt;
	t[x]=t[y];assert(cnt<(MAXN<<5)+(MAXN<<4));
	t[x].siz++;t[x].sum+=pos;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) insert(t[x].l,l,mid,pos,t[y].l);
	else insert(t[x].r,mid+1,r,pos,t[y].r);
}

int kth(int x,int l,int r,int k,int y)
{
	if(l==r) return l;
	int lsiz=t[t[x].l].siz-t[t[y].l].siz;
	int mid=(l+r)>>1;
	if(lsiz<k) return kth(t[x].r,mid+1,r,k-lsiz,t[y].r);
	else return kth(t[x].l,l,mid,k,t[y].l);
}

pair<int,ll> operator + (const pair<int,ll> &lhs,const pair<int,ll> &rhs){return make_pair(lhs.first+rhs.first,lhs.second+rhs.second);}

pair<int,ll> query(int x,int l,int r,int ql,int qr,int y)
{
	if(ql>qr) return make_pair(0,0);
	if(ql<=l&&r<=qr) return make_pair(t[x].siz-t[y].siz,t[x].sum-t[y].sum);
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr,t[y].l);
	if(ql>mid)  return query(t[x].r,mid+1,r,ql,qr,t[y].r);
	return query(t[x].l,l,mid,ql,qr,t[y].l)+query(t[x].r,mid+1,r,ql,qr,t[y].r);
}

int main()
{
	read(n);read(k);
	for(int i=1;i<=n;i++) read(a[i]),mx=max(a[i],mx);
	for(int i=1;i<=n;i++)
		insert(rt[i],0,mx,a[i],rt[i-1]);
	for(int i=k;i<=n;i++)
	{
		int Mid=kth(rt[i],0,mx,(k+1)>>1,rt[i-k]);
		pair<int,ll> le=query(rt[i],0,mx,0,Mid,rt[i-k]),ge=query(rt[i],0,mx,Mid+1,mx,rt[i-k]);
		Ans=min(Ans,1ll*le.first*Mid-le.second+ge.second-1ll*ge.first*Mid);
	}
	printf("%lld\n",Ans);
}