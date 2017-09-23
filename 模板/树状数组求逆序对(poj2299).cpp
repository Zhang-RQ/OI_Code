#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
struct node{
    int val,pos;
}In[500100];
int aa[500100];
int c[500100];
int n;
inline int lowbit(int x)
{
    return x&(-x);
}
void add(int pos,int val)
{
    for(int i=pos;i<=n;i+=lowbit(i))
    {
        c[i]+=val;
    }
    return;
}
int sum(int pos)
{
    int ret=0;
    for(int i=pos;i>=1;i-=lowbit(i))
        ret+=c[i];
    return ret;
}
bool cmp(const node &a,const node &b)
{
    return a.val<b.val;
}
int main()
{
    while(scanf("%d",&n)&&n)
    {
        memset(In,0,sizeof(In));
        memset(c,0,sizeof(c));
        long long ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&In[i].val);
            In[i].pos=i;
        }
        sort(In+1,In+1+n,cmp);
        for(int i=1;i<=n;i++)  aa[In[i].pos]=i;
        for(int i=1;i<=n;i++)
        {
            add(aa[i],1);
            ans+=i-sum(aa[i]);
        }
        printf("%lld\n",ans);
    }
}
