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
std::vector<int> v;
bool vis[1310009];
void euler()
{
    for(int i=2;i<=1299709;i++)
    {
        if(!vis[i]) v.push_back(i);
        for(int j=0;j<(signed)v.size()&&v[j]*i<=1299709;j++)
        {
            vis[i*v[j]]=1;
            if(i%v[j]==0) break;
        }
    }
}
int main()
{
    euler();
    int k;
    while(~scanf("%d",&k)&&k)
    {
        if(*lower_bound(v.begin(),v.end(),k)==k) puts("0");
        else
            printf("%d\n",*upper_bound(v.begin(),v.end(),k)-*(lower_bound(v.begin(),v.end(),k)-1));
    }
}
