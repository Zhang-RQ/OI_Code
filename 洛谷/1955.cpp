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
int fa[100010<<1],t,n;
int find(int x)
{
    if(x==fa[x]) return x;
    else return fa[x]=find(fa[x]);
}
struct node{
    int x,y,ops;
    bool operator < (const node &a) const
    {
        return ops>a.ops;
    }
}query[100010];
int arr[200020];
int main()
{
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--)
    {
        int cnt=0;
        bool flag=0;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>query[i].x>>query[i].y>>query[i].ops;
            arr[++cnt]=query[i].x;arr[++cnt]=query[i].y;
        }
        sort(arr+1,arr+1+cnt);
        cnt=unique(arr+1,arr+1+cnt)-arr-1;
        for(int i=1;i<=n;i++)
        {
            query[i].x=lower_bound(arr+1,arr+1+cnt,query[i].x)-arr;
            query[i].y=lower_bound(arr+1,arr+1+cnt,query[i].y)-arr;
        }
        for(int i=1;i<=cnt;i++) fa[i]=i;
        sort(query+1,query+1+n);
        for(int i=1;i<=n;i++)
        {
            if(query[i].ops==1) fa[find(query[i].x)]=fa[find(query[i].y)];
            else
            {
                if(find(query[i].x)==find(query[i].y)) {puts("NO");flag=1;break;}
            }
        }
        if(!flag) puts("YES");
    }
}
