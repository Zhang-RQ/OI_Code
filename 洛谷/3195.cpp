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
#define A(i) (i+sum[i])
#define B(i) (A(i)+l+1)
#define X(i) B(i)
#define Y(i) (B(i)*B(i)+dp[i])
#define slope(i,j) (1.0*(Y(j)-Y(i))/(1.0*(X(j)-X(i))))
const int MAXN=50010;
deque<int> q;
int n,l;
ll c[MAXN],sum[MAXN],dp[MAXN];
int main()
{
    scanf("%d%d",&n,&l);
    for(int i=1;i<=n;i++)
        scanf("%lld",&c[i]),sum[i]=sum[i-1]+c[i];
    q.push_back(0);
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        while(q.size()>1&&slope(*(q.begin()),*(q.begin()+1))<2.0*A(i))
            q.pop_front();
        dp[i]=dp[q.front()]+(A(i)-B(q.front()))*(A(i)-B(q.front()));
        while(q.size()>1&&slope(*(q.end()-2),i)<slope(*(q.end()-2),*(q.end()-1)))
            q.pop_back();
        q.push_back(i);
    }
    printf("%lld\n",dp[n]);
}
