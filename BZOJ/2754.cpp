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
const int MAXN=500100;
map<int,int> son[MAXN];
int par[MAXN],mx[MAXN];
int siz[MAXN],cur[MAXN],ans[MAXN];
int marked[MAXN];
int st[20100][2],len[20010][2],n,m,ccnt=0;
int s[MAXN];
int str[MAXN],tlen;
int lst=1,rt=1,cnt=1;
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
void update1(int pos,int x)
{
    for(;x&&cur[pos]!=x;pos=par[pos])
    {
        // printf("%d %d\n",x,pos);
        siz[pos]++;
        cur[pos]=x;
    }
}
void update2(int pos,int x)
{
    for(;x&&cur[pos]!=x;pos=par[pos])
    {
        ans[x]+=marked[pos];
        cur[pos]=x;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        lst=1;
        // printf("%d %d ",i,ccnt);
        scanf("%d",&len[i][0]);
        st[i][0]=ccnt+1;
        for(int j=1;j<=len[i][0];j++)
            ++ccnt,scanf("%d",&str[ccnt]),insert(str[ccnt]);
        // printf("%d %d\n",st[i][0],ccnt);
        lst=1;
        scanf("%d",&len[i][1]);
        st[i][1]=ccnt+1;
        for(int j=1;j<=len[i][1];j++)
            ++ccnt,scanf("%d",&str[ccnt]),insert(str[ccnt]);
    }
    // for(int i=1;i<=n;i++)
    // {
    //     printf("%d ",st[i][0]);
    //     for(int j=0;j<len[i][0];j++)    printf("%d ",str[st[i][0]+j]);
    //     puts("");
    // }
    for(int i=1;i<=n;i++)
    {
        for(int j=0,x=rt;j<len[i][0];j++) x=son[x][str[j+st[i][0]]],update1(x,i);
        for(int j=0,x=rt;j<len[i][1];j++) x=son[x][str[j+st[i][1]]],update1(x,i);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&tlen);
        int x=rt,flag=1;
        for(int j=1;j<=tlen;j++)
        {
            scanf("%d",&s[j]);
            if(!son[x][s[j]]||!flag) {flag=0;}
            else x=son[x][s[j]];
        }
        if(flag) printf("%d\n",siz[x]),marked[x]++;
        else puts("0");
    }
    memset(cur,0,sizeof(int)*(cnt+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=0,x=rt;j<len[i][0];j++) x=son[x][str[j+st[i][0]]],update2(x,i);
        for(int j=0,x=rt;j<len[i][1];j++) x=son[x][str[j+st[i][1]]],update2(x,i);
    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    puts("");
}
