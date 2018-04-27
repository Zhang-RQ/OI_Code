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
const int MAXN=2E5+5;
int son[MAXN][4],siz[MAXN],mx[MAXN],par[MAXN],lt;
int cnt=1,lst=1,rt=1,T,id[128],buk[MAXN],tp[MAXN];
ll ans=0;
char s[MAXN],s0[MAXN];
void insert(int x)
{
    int p=lst,np=++cnt;
    siz[np]=1;mx[np]=mx[p]+1;
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++cnt;
            siz[nq]=0;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
void dfs(int x,int len,int tot)
{
    if(len>lt) {ans+=siz[x];return;}
    for(int i=0;i<=3;i++)
    {
        if(son[x][i])
        {
            if(i==id[(int)s0[len]]) dfs(son[x][i],len+1,tot);
            else if(tot<=2) dfs(son[x][i],len+1,tot+1);
        }
    }
}
int main()
{
    id['A']=0;id['T']=1;
    id['C']=2;id['G']=3;
    scanf("%d",&T);
    while(T--)
    {
        ans=0;siz[rt]=0;
        scanf("%s%s",s+1,s0+1);
        lt=strlen(s0+1);
        rt=lst=cnt=1;
        memset(buk,0,sizeof buk);
        memset(son,0,sizeof son);
        memset(par,0,sizeof par);
        for(int i=1;s[i];i++) insert(id[(int)s[i]]);
        for(int i=1;i<=cnt;i++) buk[mx[i]]++;
        for(int i=1;i<=cnt;i++) buk[i]+=buk[i-1];
        for(int i=cnt;i>=1;i--) tp[buk[mx[i]]--]=i;
        for(int i=cnt;i>=1;i--) siz[par[tp[i]]]+=siz[tp[i]];
        dfs(rt,1,0);
        printf("%lld\n",ans);
    }
}
