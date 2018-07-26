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

ll n,_n;
vector<pair<int,int> > p;
ll ans;

void dfs(int x,int tims,ll phi,ll cur)
{
    if(tims!=0) ans+=phi*(n/cur);
    if(tims<p[x].second&&tims!=0) dfs(x,tims+1,phi*p[x].first,cur*p[x].first);
    if(tims<p[x].second&&tims==0) dfs(x,tims+1,phi*(p[x].first-1),cur*p[x].first);
    if(x<p.size()-1) dfs(x+1,0,phi,cur);
}

int main()
{
    scanf("%lld",&n);
    int lim=sqrt(n);
    ans+=n;_n=n;
    for(int i=2,t;i<=lim;i++)
    {
        if(n%i==0)
        {
            t=0;
            while(n%i==0)
                n/=i,++t;
            p.push_back(make_pair(i,t));
        }
    }
    if(n!=1) p.push_back(make_pair(n,1));
    n=_n;
    dfs(0,0,1,1);
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}