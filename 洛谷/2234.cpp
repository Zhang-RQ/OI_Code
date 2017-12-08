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
set<int> s;
int n;
int arr[40000];
ll ans;
set<int>::iterator it1;
set<int>::iterator it2;
int main()
{
    scanf("%d",&n);
    scanf("%d",&arr[1]);
    ans+=arr[1];
    s.insert(arr[1]);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&arr[i]);
        it1=it2=s.lower_bound(arr[i]);
        if(it1!=s.begin()) it1--;
        if(it2==s.end()) it2--;
        ans+=min(abs(*it1-arr[i]),abs(*it2-arr[i]));
        s.insert(arr[i]);
    }
    printf("%lld\n",ans);
}
