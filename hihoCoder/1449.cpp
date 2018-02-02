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
const int MAXN=1000010<<1;
int son[MAXN][26],siz[MAXN],mx[MAXN],par[MAXN];
int lst=1,root=1,cnt=1,n,ans[MAXN],tp[MAXN],sum[MAXN];
char str[MAXN];
void insert(int x)
{
    x-='a';
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    siz[np]=1;
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
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            mx[nq]=mx[p]+1;
            while(p&&son[p][x]==q)
                son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
void calc()
{
    int mxval=0;
    for(int i=1;i<=cnt;i++)
        sum[mx[i]]++,mxval=max(mxval,mx[i]);
    for(int i=1;i<=mxval;i++)
        sum[i]+=sum[i-1];
    for(int i=1;i<=cnt;i++)
        tp[sum[mx[i]]--]=i;
    for(int i=cnt;i>=1;i--)
    {
        siz[par[tp[i]]]+=siz[tp[i]];
        ans[mx[tp[i]]]=max(ans[mx[tp[i]]],siz[tp[i]]);
    }
    for(int i=n-1;i>=1;i--)
        ans[i]=max(ans[i],ans[i+1]);
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++)
        insert(str[i]);
    calc();
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}
