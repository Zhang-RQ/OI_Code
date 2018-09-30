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

int n,m,cnt,rt[MAXN],A[MAXN];
pair<int,int> a[MAXN];
ll Ans=0;

bool cmp(const pair<int,int> &lhs,const pair<int,int> &rhs) {return lhs.first<rhs.first||(lhs.first==rhs.first&&lhs.second>rhs.second);}

struct node{
	int l,r,v;
}t[MAXN<<7];

void insert(int &x,int l,int r,int pos,int _x)
{
	x=++cnt;
	t[x]=t[_x];
	t[x].v++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) insert(t[x].l,l,mid,pos,t[_x].l);
	else insert(t[x].r,mid+1,r,pos,t[_x].r);
}

int kth(int x,int l,int r,int k,int _x)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(t[t[x].l].v-t[t[_x].l].v>=k) return kth(t[x].l,l,mid,k,t[_x].l);
	else return kth(t[x].r,mid+1,r,k-(t[t[x].l].v-t[t[_x].l].v),t[_x].r);
}

void solve()
{
	Ans=cnt=0;
	memset(rt,0,sizeof rt);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].first,&a[i].second);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) A[i]=a[i].first;
	for(int i=1;i<=n;i++) insert(rt[i],1,100000,a[i].second,rt[i-1]);
	for(int i=1;i<=n;i++)
	{
		if(a[i].first==a[i-1].first) continue;
		int L=lower_bound(A+1,A+1+n,A[i])-A-1;
		if(L>m) break;
		if(m-L<n-i) Ans=max(Ans,1ll*A[i]*min(kth(rt[n],1,100000,m-L+1,rt[i]),a[i].second));
		else Ans=max(Ans,1ll*A[i]*a[i].second);
	}
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	for(scanf("%d",&T);T--;solve());
}