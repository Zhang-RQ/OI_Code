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
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1010;

vector<int> g[MAXN];

int n,m,e,mat[MAXN];
bool inC[MAXN];  //inC mat 为右部点

bool dfs(int x)
{
    for(int v:g[x])
        if(!inC[v])
        {
            inC[v]=1;
            if(!mat[v]||dfs(mat[v])) return mat[v]=x,1;
        }
    return 0;
}

int main()
{
    scanf("%d%d%d",&n,&m,&e);
    for(int i=1,u,v;i<=e;i++)
    {
        scanf("%d%d",&u,&v);
        if(u>n||v>m) continue;
        g[u].push_back(v);
    }
    int Ans=0;
    for(int i=1;i<=n;i++)
    {
        memset(inC,0,sizeof inC);
        Ans+=dfs(i);
    }
    printf("%d\n",Ans);
}