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
int n,k;
int main()
{
    while(~scanf("%d%d",&n,&k)&&n&&k)
        puts((n-1)%(k+1)?"Tang":"Jiang");
}
