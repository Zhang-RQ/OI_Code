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
const int P=1E9+7;
const int M=131;
char str[210],word[10][210];
int n,k,p;
int sum[210][210];
int hword[10];
int hash2(char* s)
{
    int ret=0;
    for(;*s;s++)
        ret=(ret*M+*s-'a')%P;
    return ret;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%s",str+i*20-19);
    scanf("%d",&p);
    for(int i=1;i<=p;i++)
        scanf("%s",word[i]+1),
        hword[i]=hash2(word[i]+1);
    for(int i=1;i<=n;i)
}
