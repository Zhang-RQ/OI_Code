#include<bits/stdc++.h>

using namespace std;

const int MAXN=3E5+10;

int son[MAXN*21][2],v[MAXN*21],tag,cnt=1,rt=1,n,m;
set<int> s;

void insert(int val)
{
    int x=rt;
    for(int i=20,cur;~i;--i)
    {
        v[x]++;cur=(val>>i)&1;
        if(!son[x][cur]) son[x][cur]=++cnt;
        x=son[x][cur];
    }
    v[x]++;
}

int query()
{
    int L=0,R=(1<<21)-1,ret=0,x=rt;
    for(int i=20,cur;~i;--i)
    {
        cur=(tag>>i)&1;
        int tL=L,tR=(L+R)>>1;
        if(cur)
        {
            if(v[son[x][1]]==tR-tL+1) x=son[x][0],ret|=1<<i,L=tR+1;
            else x=son[x][1],R=tR;
        }
        else
        {
            if(v[son[x][0]]==tR-tL+1) x=son[x][1],ret|=1<<i,L=tR+1;
            else x=son[x][0],R=tR;
        }
    }
    return ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        if(s.count(x)) continue;
        insert(x);s.insert(x);
    }
    for(int i=1,x;i<=m;i++)
    {
        scanf("%d",&x);
        tag^=x;printf("%d\n",query());
    }
}
