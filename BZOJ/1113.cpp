#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
int n,m,t1,t2;
int fa[MAXN];
bool mark[MAXN];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&t1,&t2);
        int a=find(t1),b=find(t2);
        if(a!=b)
        {
            fa[a]=b;
            mark[b]=(mark[a]|mark[b]);
        }
        else mark[a]=1;
    }
    for(int i=1;i<=n;i++)
        if(!mark[find(i)])
        {
            puts("NIE");
            return 0;
        }
    puts("TAK");
}
