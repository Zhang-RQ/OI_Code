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
bitset<10100> ans;
bitset<10100> now;
int main()
{
    ans.set();
    int n,m;
    scanf("%d",&n);
    while(n--)
    {
        now.reset();
        now.set(0);
        while(scanf("%d",&m)&&m!=-1) now|=(now<<m);
        ans&=now;
    }
    int tmp=0;
    for(int i=10000;i>=0;i--) if(ans[i]) {tmp=i;break;}
    printf("%d\n",tmp);
}
