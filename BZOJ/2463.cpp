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

int main()
{
    int n;
    while(scanf("%d",&n)&&n) puts(n&1?"Bob":"Alice");
    #ifdef LOCAL
        system("pause");
    #endif
}