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
struct node{
    int u,v,val;
};
bool operator < (node a,node b)
{
    return a.val<b.val;
}
vector<node> Edge;
int n,tmp,fa[110];
int find(int x)
{
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
int main()
{
    while(~scanf("%d",&n))
    {
        int ans=0;
        for(int i=1;i<=n;i++) fa[i]=i;
        Edge.clear();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                scanf("%d",&tmp);
                if(tmp!=0)
                    Edge.push_back((node){i,j,tmp});
            }
        sort(Edge.begin(),Edge.end());
        for(int i=0;i<Edge.size();i++)
        {
            int u=Edge[i].u;int v=Edge[i].v;
            if(find(u)!=find(v))
            {
                ans+=Edge[i].val;
                fa[find(u)]=find(v);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
