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

const int P=10000007;
const int Phi=9988440;

bool num[65];
ll f[65][65][2],n,ans=1;
int tot;

ll dfs(int x,int cnt,bool lim)
{
    if(cnt>x) return 0;
    if(!x) return cnt==0;
    if(~f[x][cnt][lim]) return f[x][cnt][lim];
    int lm=lim?num[x]:1;
    ll ret=0;
    for(int i=0;i<=lm;i++)
        ret+=dfs(x-1,cnt-i,lim&&i==lm);
    return f[x][cnt][lim]=ret%Phi;
}

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

int main()
{
    memset(f,-1,sizeof f);
    scanf("%lld",&n);
    while(n) num[++tot]=n&1,n>>=1;
    for(int i=2;i<=tot;i++) (ans*=ksm(i,dfs(tot,i,1)))%=P;
    printf("%lld\n",ans);   
    #ifdef LOCAL
        system("pause");
    #endif
}