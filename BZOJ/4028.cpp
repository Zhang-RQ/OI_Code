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
int blocksize,st[330],ed[330],belong[100010],a[100010],Xor[100010],Gcd[100010],n,tot,m,pos;
map<int,int> mp[330];
char opt[10];
ll val;
int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
void build(int t)
{
    mp[t].clear();
    Gcd[st[t]]=Xor[st[t]]=a[st[t]];
    mp[t][Xor[st[t]]]=st[t];
    for(int i=st[t]+1;i<=ed[t];i++)
    {
        Xor[i]=Xor[i-1]^a[i];
        if(!mp[t].count(Xor[i])) mp[t][Xor[i]]=i;
        Gcd[i]=gcd(Gcd[i-1],a[i]);
    }
}
void init()
{
    for(int i=1;i<=n;i++)
    {
        belong[i]=(i-1)/blocksize+1;
        if(!st[belong[i]]) st[belong[i]]=i;
        ed[belong[i]]=i;
    }
    tot=belong[n];
    for(int i=1;i<=tot;i++)  build(i);
}
int query(ll x)
{
    int Lgcd=0,Lxor=0;
    for(int i=1;i<=tot;i++)
    {
        int T=gcd(Lgcd,Gcd[ed[i]]);
        if(T!=Lgcd)
        {
            for(int j=st[i];j<=ed[i];j++)
                if(1ll*(Lxor^Xor[j])*gcd(Lgcd,Gcd[j])==x)  return j-1;
        }
        else if(x%T==0&&mp[i].count((x/T)^Lxor))  return mp[i][(x/T)^Lxor]-1;
        Lxor^=Xor[ed[i]];
        Lgcd=T;
    }
    return -233;
}
int main()
{
    scanf("%d",&n);
    blocksize=sqrt(n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);init();
    for(int i=1;i<=m;i++)
    {
        scanf("%s",opt+1);
        if(opt[1]=='M')
        {
            scanf("%d%lld",&pos,&val);
            ++pos;a[pos]=val;
            build(belong[pos]);
        }
        else
        {
            scanf("%lld",&val);
            int t=query(val);
            printf(t==-233?"no\n":"%d\n",t);
        }
    }
}
