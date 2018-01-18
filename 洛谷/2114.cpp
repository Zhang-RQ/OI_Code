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
const int MAXN=200010;
int n,m,ans,tmp;
int num[MAXN],op[MAXN];
char str[101];
inline int calc(int pos,int val)
{
    int ret=val<<pos;
    for(int i=1;i<=n;i++)
        switch (op[i])
        {
            case 1: ret&=((num[i]>>pos)&1)<<pos;break;
            case 2: ret|=((num[i]>>pos)&1)<<pos;break;
            case 3: ret^=((num[i]>>pos)&1)<<pos;break;
        }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%d",str+1,&num[i]);
        switch(str[1])
        {
            case 'A': op[i]=1;break;
            case 'O': op[i]=2;break;
            case 'X': op[i]=3;break;
        }
    }
    for(int i=0;i<=30&&tmp<=m;i++)
    {
        //printf("1:%d 0:%d\n",calc(i,1),calc(i,0));
        if(calc(i,0)<calc(i,1)&&(tmp|(1<<i))<=m)
            tmp|=1<<i,ans|=calc(i,1);
        else ans|=calc(i,0);
    }
    printf("%d\n",ans);
    return 0;
}
