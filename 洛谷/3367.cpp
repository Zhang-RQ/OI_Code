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
int fa[10010];
int find(int x)
{
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
int main()
{
    ios::sync_with_stdio(0);
    int n,m,t1,t2,ops;
    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        cin>>ops>>t1>>t2;
        if(ops==1) fa[find(t1)]=find(t2);
        else if(ops==2)  if(find(t1)==find(t2)) puts("Y");else puts("N");
    }
}
