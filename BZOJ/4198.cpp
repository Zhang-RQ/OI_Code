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

priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > pq;

int n,k;
ll ans,x;

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&x),pq.push(make_pair(x,1));
    int cnt=n;
    if((n-1)%(k-1)) cnt+=k-1-(n-1)%(k-1);
    for(int i=n+1;i<=cnt;i++) pq.push(make_pair(0,1));
    while(cnt>1)
    {
        ll sum=0,dep=0;
        for(int i=1;i<=k;i++)
        {
            dep=max(dep,pq.top().second);
            sum+=pq.top().first;
            pq.pop();
        }
        ans+=sum;
        pq.push(make_pair(sum,dep+1));
        cnt-=k-1;
    }
    printf("%lld\n%lld\n",ans,pq.top().second-1);
    #ifdef LOCAL
        system("pause");
    #endif
}