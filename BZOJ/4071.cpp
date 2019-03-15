#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E6+10;
const int INF=1E9;

struct node_t{
	int l,r,siz;
	ll sum;
}t[MAXN*4];

pair<int,int> a[MAXN];
int K,n,tot,rt1,rt2;
int cnt;
ll tAns,Ans;
char str1[233],str2[233];
stack<int> stk;

int nd()
{
	int ret;
	if(stk.size()) ret=stk.top(),stk.pop();
	else ret=++cnt;
	t[ret].l=t[ret].r=t[ret].siz=t[ret].sum=0;
	return ret;
}

void insert(int &x,int l,int r,int p,int v)
{
	if(!x) x=nd();
	t[x].sum+=p*v;
	t[x].siz+=v;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p,v);
	else insert(t[x].r,mid+1,r,p,v);
	if(!t[x].siz) stk.push(x),x=0;
}

pair<ll,ll> operator + (const pair<ll,ll> &l,const pair<ll,ll> &r){return make_pair(l.first+r.first,l.second+r.second);}

pair<ll,ll> query(int x,int l,int r,int ql,int qr)
{
	if(!x) return make_pair(0,0);
	if(ql<=l&&r<=qr) return make_pair(t[x].siz,t[x].sum);
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr);
	else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr);
	else return query(t[x].l,l,mid,ql,qr)+query(t[x].r,mid+1,r,ql,qr);
}

int Kth(int x,int l,int r,int k)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(k>t[t[x].l].siz) return Kth(t[x].r,mid+1,r,k-t[t[x].l].siz);
	else return Kth(t[x].l,l,mid,k);
}
	
ll Calc(int Rt)
{
	if(!Rt||!t[Rt].siz) return 0;
	int M=Kth(Rt,0,INF,(t[Rt].siz+1)>>1);
	pair<ll,ll> p=query(Rt,0,INF,0,M);
	ll ret=1ll*M*p.first-p.second+(t[Rt].sum-p.second)-1ll*M*(t[Rt].siz-p.first);
	return ret;
}

int main()
{
	scanf("%d%d",&K,&n);
	if(K==1)
	{
		int tot=0;
		for(int i=1,x,y;i<=n;i++)
		{
			scanf("%s%d%s%d",str1+1,&x,str2+1,&y);
			if(str1[1]==str2[1]) tAns+=abs(y-x);
			else insert(rt1,0,INF,x,1),insert(rt1,0,INF,y,1),++tot;
		}
		printf("%lld\n",tAns+Calc(rt1)+tot);
	}
	else
	{
		int tot=0;
		for(int i=1,x,y;i<=n;i++)
		{
			scanf("%s%d%s%d",str1+1,&x,str2+1,&y);
			if(str1[1]==str2[1]) tAns+=abs(y-x);
			else a[++tot]=make_pair(x,y);
		}
		sort(a+1,a+1+tot,[](pair<int,int> X,pair<int,int> Y){return X.first+X.second<Y.first+Y.second;});
		for(int i=1;i<=tot;i++) insert(rt2,0,INF,a[i].first,1),insert(rt2,0,INF,a[i].second,1);
		Ans=Calc(rt2);
		for(int i=1;i<=tot;i++)
		{
			insert(rt2,0,INF,a[i].first,-1),insert(rt2,0,INF,a[i].second,-1);
			insert(rt1,0,INF,a[i].first,1),insert(rt1,0,INF,a[i].second,1);
			Ans=min(Ans,Calc(rt1)+Calc(rt2));
		}
		printf("%lld\n",Ans+tAns+tot);
	}
}
