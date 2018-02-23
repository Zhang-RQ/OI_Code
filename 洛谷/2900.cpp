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
const int MAXN=50010;
#define Y(i) dp[i]
#define X(i) rel[i+1].len
#define slope(i,j) ((double)(Y(i)-Y(j))/(X(i)-X(j)))
struct block{
    int wid,len;
}in[MAXN],rel[MAXN];
int n,tot;
inline bool cmp (const block &a,const block &b)
{
    if(a.wid==b.wid) return a.len<b.len;
    return a.wid<b.wid;
}
deque<int> Q;
ll dp[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&in[i].wid,&in[i].len);
    tot=0;
    sort(in+1,in+1+n,cmp);
    rel[++tot]=in[1];
    for(int i=2;i<=n;i++)
    {
        while(tot&&rel[tot].len<=in[i].len) tot--;
        rel[++tot]=in[i];
    }
    Q.push_back(0);
    for(int i=1;i<=tot;i++)
    {
        while(Q.size()>1&&slope(*Q.begin(),*(Q.begin()+1))>(double)-rel[i].wid) Q.pop_front();
        dp[i]=Y(Q.front())+1ll*rel[i].wid*X(Q.front());
        while(Q.size()>1&&slope(*(Q.end()-2),*(Q.end()-1))<slope(*(Q.end()-2),i)) Q.pop_back();
        Q.push_back(i);
    }
    printf("%lld\n",dp[tot]);
}
