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
const int MAXN=200100;
int son[MAXN][26],mx[MAXN],par[MAXN],siz[MAXN],buk[MAXN],tp[MAXN];
char str[MAXN],vis[MAXN],str1[MAXN],tstr[MAXN];
int cnt=1,lst=1,root=1;
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
void calc_siz()
{
    int maxv=0;
    for(int i=1;i<=cnt;i++) buk[mx[i]]++,maxv=max(maxv,mx[i]);
    for(int i=1;i<=maxv;i++) buk[i]+=buk[i-1];
    for(int i=1;i<=cnt;i++) tp[buk[mx[i]]--]=i;
    for(int i=cnt;i>=1;i--)
        siz[par[tp[i]]]+=siz[tp[i]];
}
ll calc_ans(int len,int n)
{
    ll ret=0;
    memset(vis,0,sizeof vis);
    int u=root,l=0;
    for(int i=1;i<=len;i++)
    {
        while(u!=root&&!son[u][str1[i]-'a'])
            u=par[u],l=mx[u];
        if(son[u][str1[i]-'a'])
            u=son[u][str1[i]-'a'],++l;
        else u=root,l=0;
        if(l>n)
            while(par[u]&&mx[par[u]]>=l)
                u=par[u],l=mx[par[u]];
        if(l>=n&&!vis[u])
            vis[u]=1,
            ret+=siz[u];
    }
    return ret;
}
int N;
int main()
{
    scanf("%s",str+1);
    int ln=strlen(str+1);
    for(int i=1;i<=ln;i++)
        insert(str[i]);
    calc_siz();
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%s",tstr+1);
        int tlen=strlen(tstr+1);
        str1[1]='\0';
        strcat(str1+1,tstr+1);
        tstr[tlen]='\0';
        strcat(str1+1+tlen,tstr+1);
        //puts(str1+1);
        printf("%lld\n",calc_ans(tlen*2-1,tlen));

    }
    return 0;
}
