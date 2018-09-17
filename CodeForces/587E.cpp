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

const int MAXN=2E5+10;

struct Linear_Base{
    int b[32],st;
    inline int& operator [] (const int &i) {return b[i];}
    inline const int& operator [] (const int &i) const {return b[i];}
    Linear_Base(){st=0;memset(b,0,sizeof b);}
    inline void clear(){st=0;memset(b,0,sizeof b);}
    inline void insert(int val)
    {
        for(int i=30;~i;i--)
            if((val>>i)&1)
            {
                if(b[i]) val^=b[i];
                else {b[i]=val;break;}
            }
    }
    inline int count()
    {
    	int cnt=0;
    	for(int i=0;i<=30;i++)
    		if(b[i]) ++cnt;
    	return 1<<cnt;
    }
}t[MAXN<<2],Ans;

inline Linear_Base merge(const Linear_Base &lhs,const Linear_Base &rhs)
{
    Linear_Base ret=lhs;
    for(int i=30;~i;i--) if(rhs[i]) ret.insert(rhs[i]);
    ret.st=rhs.st;ret.insert(lhs.st^rhs.st);
    return ret;
}

int n,m,a[MAXN],tag[MAXN<<2];

void pushup(int x){t[x]=merge(t[x<<1],t[x<<1|1]);}

void pushdown(int x)
{
	if(tag[x])
	{
		tag[x<<1]^=tag[x];tag[x<<1|1]^=tag[x];
		t[x<<1].st^=tag[x];t[x<<1|1].st^=tag[x];
		tag[x]=0;
	}
}

void build(int x,int l,int r)
{
	if(l==r) return t[x].st=a[l],void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x);
}

void change(int x,int l,int r,int cl,int cr,int val)
{
	if(cl<=l&&r<=cr) return t[x].st^=val,tag[x]^=val,void();
	int mid=(l+r)>>1;pushdown(x);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
	if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
	pushup(x);
}

void query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return Ans=merge(Ans,t[x]),void();
	int mid=(l+r)>>1;pushdown(x);
	if(ql<=mid) query(x<<1,l,mid,ql,qr);
	if(qr>mid)  query(x<<1|1,mid+1,r,ql,qr);
}

int main()
{
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build(1,1,n);
	for(int i=1,op,l,r,k;i<=m;i++)
	{
		scanf("%d%d%d",&op,&l,&r);
		if(op==1) scanf("%d",&k),change(1,1,n,l,r,k);
		else Ans.clear(),query(1,1,n,l,r),printf("%d\n",Ans.count());
	}
}