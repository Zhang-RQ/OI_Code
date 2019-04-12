#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1<<20;

int val[MAXN],n,k,d[MAXN],f[MAXN];
vector<int> G[MAXN],Ans[30];
queue<int> q;

void add(int u,int v){G[u].push_back(v),d[v]++;}

int main()
{
    scanf("%d%d",&n,&k);
    int lim=1<<k;
    for(int i=1,x;i<=n;i++)
        scanf("%d",&x),val[x]=1;
    for(int i=0;i<k;i++)
        for(int s=0;s<lim;s++)
            if((s>>i)&1)
                add(s^(1<<i),s);
    for(int i=0;i<lim;i++)
        if(!d[i])
            q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        f[x]+=val[x];
        for(int v:G[x])
        {
            f[v]=max(f[v],f[x]);
            if(!--d[v])
                q.push(v);
        }
    }
    int tmp=0;
    for(int i=0;i<lim;i++)
        tmp=max(tmp,f[i]);
    for(int i=0;i<lim;i++)
        if(val[i])
            Ans[f[i]].push_back(i);
    puts("1");
    printf("%d\n",tmp);
    for(int i=1;i<=tmp;i++)
    {
        printf("%d ",Ans[i].size());
        for(int v:Ans[i])
            printf("%d ",v);
        puts("");
    }
}
