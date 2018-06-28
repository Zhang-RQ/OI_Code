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
#include<bitset>
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int MAXN=3E4+10;

int n,m,out[MAXN],in[MAXN],pos[MAXN],cnt,ans;
vector<int> g[MAXN],gr[MAXN];
bitset<MAXN> b[MAXN],t;
queue<int> q;

bool cmp(int a,int b) {return pos[a]<pos[b];}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
        scanf("%d%d",&u,&v),g[u].push_back(v),++out[u],++in[v],gr[v].push_back(u);
    for(int i=1;i<=n;i++)
        if(!out[i]) q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        b[x][x]=1;pos[x]=n-(cnt++);
        for(int i=0;i<gr[x].size();i++)
        {
            int v=gr[x][i];
            b[v]|=b[x];
            if(!--out[v]) q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
        if(!in[i]) q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        t.reset();
        sort(g[x].begin(),g[x].end(),cmp);
        for(int i=0;i<g[x].size();i++)
        {
            int v=g[x][i];
            if(t[v]) ++ans;
            t|=b[v];
            if(!--in[v]) q.push(v);
        }
    }
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}