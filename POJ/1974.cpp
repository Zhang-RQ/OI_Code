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
char str[1000100],str1[2000100];
int len1,len2,hw[2000100];
void init()
{
    str1[0]=str1[1]='#';
    for(int i=1;i<=len1;i++)
    {
        str1[i<<1]=str[i];
        str1[i<<1|1]='#';
    }
}
void manacher()
{
    int maxR=0,mid=1;
    for(int i=2;i<=len2;i++)
    {
        if(i<maxR)
            hw[i]=min(maxR-i,hw[2*mid-i]);
        else hw[i]=1;
        while(str1[i+hw[i]]==str1[i-hw[i]]) hw[i]++;
        if(i+hw[i]>maxR)
        {
            maxR=i+hw[i];
            mid=i;
        }
    }
}
int main()
{
    int t=0,ans;
    while(scanf("%s",str+1)&&str[1]!='E'&&str[2]!='N'&&str[3]!='D')
    {
        memset(hw,0,sizeof(hw));
        memset(str1,0,sizeof(str1));
        ans=0;
        len1=strlen(str+1);
        init();
        len2=strlen(str1+1);
        manacher();
        for(int i=1;i<=len2;i++) ans=max(ans,hw[i]);
        ++t;
        printf("Case %d: %d\n",t,ans-1);
    }
}
