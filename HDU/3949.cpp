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
const int MAXN=10010;
int T,N,Q;
ll a[MAXN],b[64],k;
vector<ll> v;
bool zero;
void build()
{
    memset(b,0,sizeof b);
    zero=0;v.clear();
    for(int i=1;i<=N;i++)
        for(int j=62;~j;j--)
            if((a[i]>>j)&1)
            {
                if(b[j]) a[i]^=b[j];
                else
                {
                    b[j]=a[i];
                    for(int k=j-1;~k;k--) if(b[k]&&(b[j]>>k)&1) b[j]^=b[k];
                    for(int k=j+1;k<=62;k++) if((b[k]>>j)&1) b[k]^=b[j];
                    break;
                }
            }
    for(int i=0;i<=62;i++)
        if(b[i]) v.push_back(b[i]);
    zero=((signed)v.size()!=N);
}
ll ask(ll k)
{
    if(zero) k--;
    ll ret=0;
    if(k>=(1ll<<v.size())) return -1;
    for(int i=0;i<(signed)v.size();i++)
        if((k>>i)&1)
            ret^=v[i];
    return ret;
}
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        scanf("%d",&N);
        for(int i=1;i<=N;i++)
            scanf("%lld",&a[i]);
        build();
        scanf("%d",&Q);
        printf("Case #%d:\n",t);
        while(Q--)
            scanf("%lld",&k),printf("%lld\n",ask(k));
    }
}
