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
const int MAXN=1010;
map<int,int> son[MAXN];
int mx[MAXN],par[MAXN];
int lst=1,rt=1,cnt=1;
int s[MAXN][MAXN],x,ls,tp[MAXN],buk[MAXN];
int len[MAXN],n,ans[MAXN],lx[MAXN];
void insert(int x)
{
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
            son[nq]=son[q];
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        }
    }
    lst=np;
}
void calc()
{
    for(int i=1;i<=cnt;i++) buk[mx[i]]++;
    for(int i=1;i<=len[1];i++) buk[i]+=buk[i-1];
    for(int i=cnt;i>=1;i--) tp[buk[mx[i]]--]=i;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&len[i]);
        ls=0;
        for(int j=1;j<=len[i];j++)
            scanf("%d",&x),s[i][j]=x-ls,ls=x;
    }
    for(int i=1;i<=len[1];i++) insert(s[1][i]);
    for(int i=1;i<=cnt;i++) ans[i]=mx[i];
    calc();
    for(int i=2;i<=n;i++)
    {
        int pos=rt,l=0;memset(lx,0,sizeof lx);
        for(int j=1;j<=len[i];j++)
        {
            while(pos!=rt&&!son[pos][s[i][j]]) pos=par[pos],l=mx[pos];
            if(son[pos][s[i][j]]) pos=son[pos][s[i][j]],l++;
            else pos=rt,l=0;
            lx[pos]=max(lx[pos],l);
        }
        for(int j=cnt;j>=1;j--) lx[par[tp[j]]]=max(lx[par[tp[j]]],lx[tp[j]]);
        for(int j=1;j<=cnt;j++) ans[j]=min(ans[j],lx[j]);
    }
    int anss=0;
    for(int i=1;i<=cnt;i++) anss=max(anss,ans[i]);
    printf("%d\n",anss+1);
}
