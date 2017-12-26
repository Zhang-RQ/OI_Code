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
typedef unsigned long long ull;
const int MAXN=50010;
const int MAXM=50010;
int siz,n,m,arr[MAXN];
int now,col[MAXN],L,R;
ll ans,tot,tmp;
struct query{
    int l,r,id;
    ll ans1,ans2;
    bool operator < (query a) const
    {
        if(l/siz!=a.l/siz) return l/siz<a.l/siz;
        else return r<a.r;
    }
}Q[MAXM];
bool cmp(query a,query b)
{
    return a.id<b.id;
}
ll C2(ll x)
{
    return (x-1)*x/2;
}
void add(int pos)
{
    ++col[arr[pos]];
    ++tot;
    if(col[arr[pos]]>2)
        ans=ans-C2(col[arr[pos]]-1)+C2(col[arr[pos]]);
    else if(col[arr[pos]]==2)
        ans+=1;
}
void del(int pos)
{
    --col[arr[pos]];
    --tot;
    if(col[arr[pos]]>=2)
        ans=ans-C2(col[arr[pos]]+1)+C2(col[arr[pos]]);
    else if(col[arr[pos]]==1)
        ans-=1;
}
ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d%d",&n,&m);
    siz=sqrt(n);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
    sort(Q+1,Q+1+m);
    L=R=0;tot=1;
    for(int i=1;i<=m;i++)
    {
        while(R<Q[i].r)  add(++R);
        while(R>Q[i].r)  del(R--);
        while(L<Q[i].l)  del(L++);
        while(L>Q[i].l)  add(--L);
        if(ans)
        {
            tmp=gcd(ans,C2(tot));
            Q[i].ans1=1LL*ans/tmp;
            Q[i].ans2=1LL*C2(tot)/tmp;

        }
        else Q[i].ans2=1;
    }
    sort(Q+1,Q+1+m,cmp);
    for(int i=1;i<=m;i++)
        printf("%lld/%lld\n",Q[i].ans1,Q[i].ans2);
}
