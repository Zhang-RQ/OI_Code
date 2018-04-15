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
const int MAXN=1E5+10;
struct aaa{
    ll t[1000005];
    void add(int pos,int val)
    {
        for(int i=pos;i<=1000000;i+=i&-i)
            t[i]+=val;
    }
    ll query(int pos)
    {
        ll ret=0;
        for(int i=pos;i>=1;i-=i&-i)
            ret+=t[i];
        return ret;
    }
    void clear()
    {
        memset(t,0,sizeof t);
    }
}zero,one;
int a[MAXN];
ll sum[MAXN],maxv,ans;
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&sum[i]),sum[i]+=sum[i-1],maxv=max(maxv,sum[i]);
    for(int i=0;i<=20;i++)
    {
        if((1<<i)>maxv) break;
        zero.clear();one.clear();
        zero.add(1,1);
        int flag=0,cnt=0;
        for(int j=1;j<=n;j++)
        {
            int tmp=sum[j]&(1<<i),now=0;
            if(tmp) now=zero.query(a[j]+1)+one.query(1000000)-one.query(a[j]+1);
            else now=one.query(a[j]+1)+zero.query(1000000)-zero.query(a[j]+1);
            if(now%2) cnt^=1;
            if(tmp>0) one.add(a[j]+1,1);
            else zero.add(a[j]+1,1);
            a[j]|=tmp;
        }
        if(cnt) ans+=(1<<i);
    }
    printf("%lld\n",ans);
}
