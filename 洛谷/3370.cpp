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
#include<climits>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const unsigned int mod1=1222827239;
const unsigned int mod2=1610612741;
struct node{
    ull hash1,hash2;
    bool operator ==(const node &a)const
    {
        return hash1==a.hash1&&hash2==a.hash2;
    }
}S[10010];
bool cmp(node a,node b)
{
    if(a.hash1!=b.hash1) return a.hash1<b.hash1;
    else return a.hash2<b.hash2;
}
ull hash1(char* s)
{
    ull ret=0;
    for(int i=0;i<(signed)strlen(s);i++)
        ret=(ret*131+s[i])%mod1;
    return ret;
}
ull hash2(char* s)
{
    ull ret=0;
    for(int i=0;i<(signed)strlen(s);i++)
        ret=(ret*131+s[i])%mod2;
    return ret;
}
int main()
{
    char str[1600];
    int n;
    int tmp=0,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        S[i].hash1=hash1(str);
        S[i].hash2=hash2(str);
    }
    sort(S+1,S+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        if(S[tmp]==S[i]) continue;
        tmp=i;
        ans++;
    }
    printf("%d\n",ans);
}
