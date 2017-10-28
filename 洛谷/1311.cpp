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
vector<int> hotel[60];
int p[200100],col[200100],first[200100];
int n,P,k;
ll ans=0;
void get_first()
{
    first[n+1]=n+1;
    for(int i=n;i>=1;i--)
    {
        if(p[i]<=P) first[i]=i;
        else first[i]=first[i+1];
    }
}
int main()
{
    scanf("%d%d%d",&n,&k,&P);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&col[i],&p[i]);
        hotel[col[i]].push_back(i);
    }
    get_first();
    for(int i=0;i<k;i++)
    {
        int r=0;
        for(int j=0;j<hotel[i].size();j++)
        {
            r=max(r,j+1); //把单调指针提到j的后面
            while(hotel[i][r]<first[hotel[i][j]]&&r<hotel[i].size())//注意单调指针不要越界
                r++;
            ans+=hotel[i].size()-r;
        }
    }
    printf("%lld\n",ans);
}
