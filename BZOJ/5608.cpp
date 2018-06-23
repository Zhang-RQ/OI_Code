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
const int P=1E9+7;
const int MAXN=1E6+10;
const int inv2=500000004;
const int inv6=166666668;
map<int,ll> S;
ll ans[MAXN];
void init()
{
    for(int i=1;i<MAXN;i++)
        ans[i]=1ll*(i-1)*(i-2)%P;
    for(int i=1;i<MAXN;i++)
        for(int j=2*i;j<MAXN;j+=i)
            ans[j]=(ans[j]-ans[i]+P)%P;
    for(int i=1;i<MAXN;i++)
        (ans[i]+=ans[i-1])%=P;
}
ll prefix_sum(int x) {return (1ll*x*(x+1)%P*(2*x+1)%P*inv6%P-3ll*x*(x+1)%P*inv2%P+2ll*x%P+P)%P;}
ll ask(int x)
{
    if(x<MAXN) return ans[x];
    if(S.find(x)!=S.end()) return S[x];
    ll ret=prefix_sum(x);
    for(int i=2,pos;i<=x;i=pos+1)
    {
        pos=x/(x/i);
        ret=(ret-(pos-i+1)*ask(x/i)%P+P)%P;
    }
    return S[x]=ret;
}
void solve()
{
    int n;
    scanf("%d",&n);
    printf("%lld\n",ask(n));
}
int main()
{
    int T;init();
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}