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
const ull Map_P=23333333;
const ull P=998244353;
const int MAXNODE=10000010;
const int base=233;
const int MAXN=2E5+10;
const int MAXK=51;
int n,m,pre[MAXN],nxt[MAXN],cnt[11],val[MAXN];
ull bin[MAXN],tp[150],h[MAXN];
char s[MAXN];
struct HashMap{
    int head[Map_P+10],cnt;
    struct node{
        int nxt,val;
        ull x;
    }nd[MAXNODE];
    void add(ull x,int val)
    {
        int t=x%Map_P+1;
        for(int i=head[t];i;i=nd[i].nxt)
            if(nd[i].x==x)
            {
                nd[i].val+=val;
                return;
            }
        nd[++cnt].nxt=head[t];nd[cnt].x=x;
        nd[cnt].val=val;head[t]=cnt;
        assert(cnt<MAXNODE);
    }
    int query(ull x)
    {
        int t=x%Map_P+1;
        for(int i=head[t];i;i=nd[i].nxt)
            if(nd[i].x==x) return nd[i].val;
        return 0;
    }
}mp;
void merge(int x,int y)
{
    int l=MAXK,r=MAXK-1;
    nxt[x]=y;pre[y]=x;
    memset(tp,0,sizeof tp);
    while(x&&l>1) tp[--l]=val[x],x=pre[x];
    while(y&&r<MAXK<<1) tp[++r]=val[y],y=nxt[y];
    for(int i=1;i<=r;i++) h[i]=h[i-1]*base+tp[i];
    for(int i=l;i<MAXK;i++)
        for(int j=r;j>=MAXK;j--)
            mp.add(h[j]-h[i-1]*bin[j-i+1],1);
}
void split(int x)
{
    int l=MAXK,r=MAXK-1,y=nxt[x];
    nxt[x]=pre[y]=0;
    memset(tp,0,sizeof tp);
    while(x&&l>1) tp[--l]=val[x],x=pre[x];
    while(y&&r<MAXK<<1) tp[++r]=val[y],y=nxt[y];
    for(int i=1;i<=r;i++) h[i]=h[i-1]*base+tp[i];
    for(int i=l;i<MAXK;i++)
        for(int j=r;j>=MAXK;j--)
            mp.add(h[j]-h[i-1]*bin[j-i+1],-1);
}
ll query(int k)
{
    ll ret=1;
    if(k==1)
        for(int i=1;s[i];i++)
            (ret*=cnt[s[i]-'0'])%=P;
    else
    {
        h[0]=0;
        for(int i=1;s[i];i++) h[i]=h[i-1]*base+s[i]-'0';
        for(int i=k;s[i];i++)
            (ret*=mp.query(h[i]-h[i-k]*bin[k]))%=P;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    bin[0]=1;
    for(int i=1;i<=n;i++) 
    {
        bin[i]=bin[i-1]*base;
        scanf("%d",&val[i]);
        cnt[val[i]]++;
    }
    for(int i=1,opt,x,y;i<=m;i++)
    {
        scanf("%d",&opt);
        if(opt==1) scanf("%d%d",&x,&y),merge(x,y);
        else if(opt==2) scanf("%d",&x),split(x);
        else if(opt==3) scanf("%s%d",s+1,&x),printf("%lld\n",query(x));
    }
    #ifdef LOCAL
        system("pause");
    #endif
}