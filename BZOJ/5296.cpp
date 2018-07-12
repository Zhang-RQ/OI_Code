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

int P,g,n,A,B,xA,xB;

map<int,int> mp;

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

int BSGS(int res) //g^ret=res
{
    int sq=sqrt(P);
    ll t1=ksm(res,P-2),t2=ksm(g,sq);
    for(int i=0;i<=sq+1;i++)
    {
        if(mp.count(t1)) return i*sq+mp[t1];
        (t1*=t2)%=P;
    }
    return 0;
}

int main()
{
    scanf("%d%d",&g,&P);
    int sq=sqrt(P);
    for(int i=0;i<=sq+1;i++) mp[1ll*ksm(ksm(g,i),P-2)%P]=i;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d",&A,&B);
        xA=BSGS(A);xB=BSGS(B);
        printf("%lld\n",ksm(g,1ll*xA*xB));
    }
    #ifdef LOCAL
        system("pause");
    #endif
}