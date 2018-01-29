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
int son[MAXN][26],par[MAXN],mx[MAXN],mn[MAXN],tp[MAXN],sum[MAXN];
int cnt=1,lst=1,root=1;
char str[MAXN];
void insert(int x)
{
    x-='a';
    int p=lst,np=++cnt;
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
            par[np]=par[q]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q)
                son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
ll ans=0;
int n;
void calc()
{
    for(int i=2;i<=cnt;i++)
        ans+=mx[i]-(mx[par[i]]+1)+1;
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++)
        insert(str[i]);
    calc();
    printf("%lld\n",ans);
}
