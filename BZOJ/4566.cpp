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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=400100;
int son[MAXN][26],par[MAXN],mx[MAXN],siz[MAXN];
int buk[MAXN],tp[MAXN];
ll sum[MAXN];
int root=1,lst=1,cnt=1;
void insert(int x)
{
    x-='a';
    int p=lst,np=++cnt;
    siz[np]=1;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x])
        son[p][x]=np,p=par[p];
    if(!p)
        par[np]=root;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1)
            par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q)
                son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
void calc()
{
    int maxv=0;
    for(int i=1;i<=cnt;i++) buk[mx[i]]++,maxv=max(mx[i],maxv);
    for(int i=1;i<=maxv;i++) buk[i]+=buk[i-1];
    for(int i=1;i<=cnt;i++) tp[buk[mx[i]]--]=i;
    for(int i=cnt;i>=1;i--) siz[par[tp[i]]]+=siz[tp[i]];
    siz[root]=0;
    for(int i=1;i<=cnt;i++)
    {
        int p=tp[i];
        sum[p]=siz[p]*(mx[p]-mx[par[p]])+sum[par[p]];
    }
}
char str1[MAXN],str2[MAXN];
ll ans=0;
int u,l;
int main()
{
    scanf("%s%s",str1+1,str2+1);
    for(int i=1;str1[i];i++)
        insert(str1[i]);
    calc();
    u=root;l=0;
    for(int i=1;str2[i];i++)
    {
        int t=str2[i]-'a';
        while(u&&!son[u][t])
            u=par[u],l=mx[u];
        if(!son[u][t]) u=root;
        else ++l,u=son[u][t],ans+=sum[par[u]]+1ll*(l-mx[par[u]])*siz[u];
    }
    printf("%lld\n",ans);
    return 0;
}
