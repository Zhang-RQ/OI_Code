%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
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
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define dwn(i,s,t) for(int i=s;i>=t;i--)
pair<ll,ll> f[10][20][10];
int bit[20],m;
ll n;
int main()
{
    for(int i=1;i<=9;i++)
        for(int j=0;j<=9;j++)
            if(i>j) f[i][0][j]=make_pair(1,j-i+10);
            else f[i][0][j]=make_pair(2,10-i);
    for(int len=1;len<=19;len++)
        for(int i=1;i<=9;i++)
            for(int j=0;j<=9;j++)
            {
                ll cur=j,cnt=0;
                for(int x=9;x>=0;x--) cnt+=f[max(i,x)][len-1][cur].first,cur=f[max(i,x)][len-1][cur].second;
                f[i][len][j]=make_pair(cnt,cur);
            }
    scanf("%lld",&n);
    if(!n) {puts("0");return 0;}
    if(n<=9) {puts("1");return 0;}
    ll ans=0,cur=n%10,n0=n;
    while(n0) bit[++m]=n0%10,n0/=10;
    for(int i=2;i<=m-1;i++)
    {
        int C=0;
        for(int j=i+1;j<=m;j++) C=max(C,bit[j]);
        int k=(i==2)?bit[i]:bit[i]-1;
        for(int j=k;j>=0;j--) ans+=f[max(C,j)][i-2][cur].first,cur=f[max(C,j)][i-2][cur].second;
    }
    int k=(m==2)?bit[m]:bit[m]-1;
    for(int i=k;i>=1;i--) ans+=f[i][m-2][cur].first,cur=f[i][m-2][cur].second;
    for(int i=m-3;i>=0;i--) for(int j=9;j>=1;j--) ans+=f[j][i][cur].first,cur=f[j][i][cur].second;
    printf("%lld\n",ans+1);
}
