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
const int MAXN=2000100;
const int P=1E9+7;
int son[MAXN][12],par[MAXN],mx[MAXN],in[MAXN],siz[MAXN];
int lst=1,root=1,cnt=1,n,lstpos=1;
ll sum[MAXN],ans;
char str[MAXN];
void insert(int x)
{
    x-='0';
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x])
        son[p][x]=np,p=par[p],++in[np];
    if(!p)
        par[np]=root;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) //max[q]==min[q]
            par[np]=q;
        else
        {
            int nq=++cnt;
            par[nq]=par[q];
            par[np]=par[q]=nq;
            mx[nq]=mx[p]+1;
            memcpy(son[nq],son[q],sizeof son[nq]);
            for(int i=0;i<=10;i++)
                if(son[nq][i])
                    ++in[son[nq][i]];
            while(p&&son[p][x]==q)
                son[p][x]=nq,p=par[p],++in[nq],--in[q];
        }
    }
    lst=np;
}
void calc()
{
    queue<int> q;
    siz[root]=1;
    q.push(root);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=0;i<=10;i++)
            if(son[x][i])
            {
                if(!(--in[son[x][i]]))
                    q.push(son[x][i]);
                if(i!=10) siz[son[x][i]]+=siz[x];
                if(i!=10) (sum[son[x][i]]+=(sum[x]*10+i*siz[x])%P)%=P;
            }
        (ans+=sum[x])%=P;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+lstpos);
        lstpos+=strlen(str+lstpos);
        if(i!=n) str[lstpos++]=':';
    }
    lstpos-=1;
    for(int i=1;i<=lstpos;i++)
        insert(str[i]);
    calc();
    printf("%lld\n",ans);
}
