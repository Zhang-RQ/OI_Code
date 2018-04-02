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
const int MAXN=200010;
int son[MAXN][26],par[MAXN],mx[MAXN],co[MAXN],cur[MAXN],n,k;
int rt=1,lst=1,cnt=1,tp[MAXN],buk[MAXN],st[MAXN],ed[MAXN];
char str[MAXN];
ll dp[MAXN];
void insert(int x)
{
    x-='a';
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
void calc()
{
    int mxv=0;
    for(int i=1;i<=cnt;i++) buk[mx[i]]++,mxv=max(mxv,mx[i]);
    for(int i=1;i<=mxv;i++)  buk[i]+=buk[i-1];
    for(int i=cnt;i>=1;i--) tp[buk[mx[i]]--]=i;
}
void solve()
{
    for(int i=1;i<=n;i++)
    {
        int p=rt;
        for(int j=st[i];j<=ed[i];j++)
        {
            p=son[p][str[j]-'a'];
            int tmp=p;
            while(tmp&&cur[tmp]!=i) co[tmp]++,cur[tmp]=i,tmp=par[tmp];
        }
    }
    calc();
    for(int i=1;i<=cnt;i++)
        dp[tp[i]]=dp[par[tp[i]]]+(co[tp[i]]>=k?mx[tp[i]]-mx[par[tp[i]]]:0);
    for(int i=1;i<=n;i++)
    {
        int p=rt;ll ans=0;
        for(int j=st[i];j<=ed[i];j++)
        {
            p=son[p][str[j]-'a'];
            ans+=dp[p];
        }
        printf("%lld ",ans);
    }
    puts("");
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+(ed[i-1]+1));
        st[i]=ed[i-1]+1;ed[i]=st[i]+strlen(str+(ed[i-1]+1))-1;
    }
    for(int i=1;i<=n;i++)
    {
        lst=1;
        for(int j=st[i];j<=ed[i];j++)  insert(str[j]);
    }
    solve();
}
