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
const double phi=(sqrt(5.0)+1)/2.0;
int n,m;
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        if(n<m) swap(n,m);
        puts((int)((n-m)*phi)==m?"0":"1");
    }
}
