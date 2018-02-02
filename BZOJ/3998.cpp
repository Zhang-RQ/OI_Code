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
const int MAXN=((int)5E5+10)<<1;
int son[MAXN][26],par[MAXN],mx[MAXN];
int sum[2][MAXN],siz[2][MAXN],buk[MAXN],tp[MAXN];
int root=1,lst=1,cnt=1;
char str[MAXN];
void insert(int x)
{
    x-='a';
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    siz[1][np]=1;
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
void calc()
{
    int maxv=0;
    for(int i=1;i<=cnt;i++) buk[mx[i]]++,maxv=max(maxv,mx[i]);
    for(int i=1;i<=maxv;i++) buk[i]+=buk[i-1];
    for(int i=1;i<=cnt;i++) tp[buk[mx[i]]--]=i;
    for(int i=cnt;i>=1;i--)
    {
        int p=tp[i];
        siz[1][par[p]]+=siz[1][p];
        siz[0][p]=1;
    }
    siz[1][root]=siz[0][root]=0;
    for(int i=cnt;i>=1;i--)
    {
        int p=tp[i];
        sum[0][p]=siz[0][p];sum[1][p]=siz[1][p];
        for(int j=0;j<26;j++)
            if(son[p][j])
                sum[0][p]+=sum[0][son[p][j]],
                sum[1][p]+=sum[1][son[p][j]];
    }
}
int stk[MAXN],top,x,y;
void query(int x,int rk,bool k)
{
    if(rk<=siz[k][x]) return;
    rk-=siz[k][x];
    for(int i=0;i<26;i++)
        if(son[x][i])
        {
            if(rk<=sum[k][son[x][i]])
                {stk[++top]=i,query(son[x][i],rk,k);break;}
            else rk-=sum[k][son[x][i]];
        }

}
int main()
{
    scanf("%s",str+1);
    for(int i=1;str[i];i++)
        insert(str[i]);
    calc();
    top=0;
    scanf("%d%d",&x,&y);
    //printf("tot=%d\n",sum[x][root]);
    if(y>sum[x][root]) {puts("-1");return 0;}
    query(root,y,x);
    for(int i=1;i<=top;i++)
        putchar(stk[i]+'a');
    puts("");
}
