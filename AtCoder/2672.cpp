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

struct peo{
	ll a,b;
}p[MAXN];

int x,y,z,n;
ll Ans=-(1ll<<60),Csum,lAns[MAXN];
priority_queue<ll,vector<ll>,greater<ll> > pq;

int main()
{
	scanf("%d%d%d",&x,&y,&z);
	n=x+y+z;
	for(int i=1,a,b,c;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		p[i].a=a-c;p[i].b=b-c;
		Csum+=c;
	}
	sort(p+1,p+1+n,[](peo a,peo b)->bool{return a.a-a.b>b.a-b.b;});
	ll sum=0;
	for(int i=1;i<=x;i++)
	{
		sum+=p[i].a;
		pq.push(p[i].a);
	}
	for(int i=x;i<=x+z;i++)
	{
		lAns[i]=sum;
		sum+=p[i+1].a;
		pq.push(p[i+1].a);
		sum-=pq.top();pq.pop();
	}
	while(!pq.empty()) pq.pop();
	sum=0;
	for(int i=n;i>=x+z+1;i--)
	{
		sum+=p[i].b;
		pq.push(p[i].b);
	}
	for(int i=x+z+1;i>x;i--)
	{
		Ans=max(Ans,lAns[i-1]+sum);
		sum+=p[i-1].b;
		pq.push(p[i-1].b);
		sum-=pq.top();pq.pop();
	}
	printf("%lld\n",Ans+Csum);
}