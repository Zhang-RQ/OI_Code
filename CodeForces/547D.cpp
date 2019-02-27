#include<bits/stdc++.h>

using namespace std;

const int MAXN=4E5+10;
const int LIM=2E5;

int n,X[MAXN],Y[MAXN];
multiset<int> g[MAXN];
map<pair<int,int>,int> M;

void dfs(int x)
{
    if(!g[x].size()) return;
    int v=*g[x].begin();
    g[x].erase(g[x].find(v));g[v].erase(g[v].find(x));
    M[{x,v}]=1;dfs(v);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&X[i],&Y[i]),g[X[i]].insert(Y[i]+LIM),g[Y[i]+LIM].insert(X[i]);
    int lst=0;
    for(int i=1;i<=LIM<<1;i++)
    {
        if(g[i].size()&1)
        {
            if(lst) g[lst].insert(i),g[i].insert(lst),lst=0;
            else lst=i;
        }
    }
    for(int i=1;i<=LIM<<1;i++) dfs(i);
    for(int i=1;i<=n;i++) putchar("rb"[M[{X[i],Y[i]+LIM}]]);
    puts("");
}
