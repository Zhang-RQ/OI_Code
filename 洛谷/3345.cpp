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

const int MAXN=1E6+10;

priority_queue<pair<int,int> > pq;
int Ans,n,a[MAXN],b[MAXN];
bool U[MAXN];
ll Sum;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
	{
		Sum+=a[i];
		if(Sum>=b[i]) Sum-=b[i],++Ans,pq.push(make_pair(b[i],i)),U[i]=1;
		else if(pq.size()&&pq.top().first+Sum>=b[i])
		{
			if(pq.top().first<=b[i]) continue;
			U[pq.top().second]=0;U[i]=1;
			Sum+=pq.top().first;Sum-=b[i];
			pq.pop();pq.push(make_pair(b[i],i));
		}
	}
	printf("%d\n",Ans);
	for(int i=1;i<=n;i++)
		if(U[i])
			printf("%d ",i);
	puts("");
}