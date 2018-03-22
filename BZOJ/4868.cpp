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
const int MAXN=100100;
int n,m;
ull t[MAXN],b[MAXN],A,B,C,mx;
ull sumt[MAXN],sumb[MAXN],ans=1ll<<60;
int main()
{
    scanf("%llu%llu%llu",&A,&B,&C);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%llu",&t[i]);
    sort(t+1,t+1+n);
    for(int i=1;i<=n;i++) sumt[i]=sumt[i-1]+t[i];
    for(int i=1;i<=m;i++)
        scanf("%lld",&b[i]),mx=max(mx,b[i]);
    sort(b+1,b+1+m);
    for(int i=m;i>=1;i--) sumb[i]=sumb[i+1]+b[i];
    for(ll i=1;i<=mx;i++) //枚举最后判完的卷子在i天
    {
        ull tmp=0;
        int pos1=lower_bound(t+1,t+1+n,i)-t,pos2=upper_bound(b+1,b+1+m,i)-b;
        if(t[pos1]>=i) pos1--;
        if(pos1!=0)
        {
            if(C>2000000000) continue;
            tmp=C*(pos1*i-sumt[pos1]);
        }
        if(pos2<=m)
        {
            ull tr=sumb[pos2]-(m-pos2+1)*i;
            if(A>=B) tmp+=tr*B;
            else
            {
                ull jian=min(i*(pos2-1)-(sumb[1]-sumb[pos2]),tr);
                tmp+=jian*A+(tr-jian)*B;
            }
        }
        // printf("%lld\n",tmp);
        ans=min(ans,tmp);
    }
    printf("%llu\n",ans);
}
