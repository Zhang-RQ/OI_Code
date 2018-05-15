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
int n;
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        if(n==1||n==2) puts("Alice");
        else if(n==3) puts("Bob");
        else puts("Bob");
    }
}
