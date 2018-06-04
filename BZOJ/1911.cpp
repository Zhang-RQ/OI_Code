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
const int MAXN=1E6+10;
#define X(i) (s[i])
#define Y(i) (a*s[i]*s[i]-b*s[i]+f[i])
#define slope(i,j) ((1.0*Y(j)-Y(i))/(1.0*X(j)-X(i)))
ll s[MAXN],f[MAXN],a,b,c;
deque<int> q;
int n;
int main()
{
    scanf("%d",&n);
    scanf("%lld%lld%lld",&a,&b,&c);
    for(int i=1,t;i<=n;i++) scanf("%d",&t),s[i]=s[i-1]+t;
    f[0]=0;
    q.push_back(0);
    for(int i=1;i<=n;i++)
    {
        while(q.size()>1&&slope(*(q.begin()),*(q.begin()+1))>2.0*a*s[i]) q.pop_front();
        f[i]=-2*a*X(q.front())*s[i]+Y(q.front())+a*s[i]*s[i]+b*s[i]+c;
        while(q.size()>1&&slope(*(q.end()-2),*(q.end()-1))<=slope(*(q.end()-2),i)) q.pop_back();
        q.push_back(i);
    }
    printf("%lld\n",f[n]);
    #ifdef LOCAL
        system("pause");
    #endif
}