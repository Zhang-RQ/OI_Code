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
int cow[10100],n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&cow[i]);
    sort(cow+1,cow+1+n);
    printf("%d\n",cow[n/2+1]);
}
