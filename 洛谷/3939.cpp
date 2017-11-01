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
std::vector<int> v[300010];
int arr[300010];
int n,m;
inline void change(int x)
{
    int posx=arr[x],posxx=arr[x+1];
    if(posx==posxx) return;
    swap(*lower_bound(v[posx].begin(),v[posx].end(),x),*lower_bound(v[posxx].begin(),v[posxx].end(),x+1));
    swap(arr[x],arr[x+1]);
    return;
}
inline int query(int l,int r,int c)
{
    vector<int>::iterator right=lower_bound(v[c].begin(),v[c].end(),r);
    vector<int>::iterator left=lower_bound(v[c].begin(),v[c].end(),l);
    while(*left<l) left++;
    while(*right>r) right--;
    printf("%d %d\n",*left,*right);
    if(right-left<0) return 0;
    return right-left+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]),
        v[arr[i]].push_back(i);
    int ops,t1,t2,t3;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&ops);
        if(ops==1)
        {
            scanf("%d%d%d",&t1,&t2,&t3);
            printf("%d\n",query(t1,t2,t3));
        }
        if(ops==2)
        {
            scanf("%d",&t1);
            change(t1);
        }
    }
}
