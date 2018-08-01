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

const int MAXN=50010;
const int MAXM=1010;
const int P=10007;

int n,m,a[MAXN],s[MAXN],ans1,ans2;

namespace solve1{
    bool check(int x)
    {
        int cnt=0,sum=0;
        for(int i=1;i<=n;i++)
        {
            if(sum+a[i]>x) sum=0,++cnt;
            sum+=a[i];
        }
        if(sum) ++cnt;
        return cnt<=m;
    }
    void solve()
    {
        int L=1,R=s[n];
        for(int i=1;i<=n;i++) L=max(L,a[i]);
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(check(mid)) ans1=mid,R=mid-1;
            else L=mid+1;
        }
    }
}

namespace solve2{
    int f[MAXN],tf[MAXN];
    inline void solve()
    {
        for(int i=1;s[i]<=ans1;i++) f[i]=1;
        for(int i=1;i<=m-1;i++)
        {
            int sum=f[1],L=1;
            for(int j=2;j<=n;j++)
            {
                while(s[j]-s[L]>ans1)
                    sum=((sum-f[L])%P+P)%P,L++;
                tf[j]=sum;
                (sum+=f[j])%=P;
            }
            (ans2+=tf[n])%=P;
            memcpy(f,tf,sizeof f);
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);++m;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    solve1::solve();solve2::solve();
    printf("%d %d\n",ans1,ans2);
    #ifdef LOCAL
        system("pause");
    #endif
}