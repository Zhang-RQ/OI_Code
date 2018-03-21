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
char str1[51000100],str2[51000010];
int len1,len2;
int hw[101000010];
void init()
{
    str2[0]=str2[1]='#';
    for(int i=1;i<=len1;++i)
    {
        str2[i<<1]=str1[i];
        str2[i<<1|1]='#';
    }
}
void manacher()
{
    int maxR=0,mid=0;
    for(int i=2;i<=len2;++i)
    {
        if(i<maxR)
            hw[i]=min(hw[2*mid-i],maxR-i);
        else hw[i]=1;
        while(str2[i-hw[i]]==str2[i+hw[i]]) ++hw[i];
        if(hw[i]+i>maxR)
        {
            maxR=hw[i]+i;
            mid=i;
        }
    }
}
int main()
{
    scanf("%s",str1+1);
    int ans=0;
    len1=strlen(str1+1);
    init();
    len2=strlen(str2);
    manacher();
    for(int i=1;i<=len2;++i) ans=max(ans,hw[i]);
    printf("%d\n",ans-1);
}
